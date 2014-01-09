/* Copyright (C) 2001-2004 Bart Massey and Jamey Sharp.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Except as contained in this notice, the names of the authors or their
 * institutions shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the authors.
 */

/* Stuff that reads stuff from the server. */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "xcb.h"
#include "xcbext.h"
#include "xcbint.h"
#if USE_POLL
#include <poll.h>
#else
#include <sys/select.h>
#endif

#define XCB_ERROR 0
#define XCB_REPLY 1
#define XCB_XGE_EVENT 35

struct event_list {
    xcb_generic_event_t *event;
    struct event_list *next;
};

struct reply_list {
    void *reply;
    struct reply_list *next;
};

typedef struct pending_reply {
    uint64_t first_request;
    uint64_t last_request;
    enum workarounds workaround;
    int flags;
    struct pending_reply *next;
} pending_reply;

typedef struct reader_list {
    unsigned int request;
    pthread_cond_t *data;
    struct reader_list *next;
} reader_list;

static void wake_up_next_reader(xcb_connection_t *c)
{
    int pthreadret;
    if(c->in.readers)
        pthreadret = pthread_cond_signal(c->in.readers->data);
    else
        pthreadret = pthread_cond_signal(&c->in.event_cond);
    assert(pthreadret == 0);
}

static int read_packet(xcb_connection_t *c)
{
    xcb_generic_reply_t genrep;
    uint64_t length = 32;
    uint64_t eventlength = 0; /* length after first 32 bytes for GenericEvents */
    uint64_t bufsize;
    void *buf;
    pending_reply *pend = 0;
    struct event_list *event;

    /* Wait for there to be enough data for us to read a whole packet */
    if(c->in.queue_len < length)
        return 0;

    /* Get the response type, length, and sequence number. */
    memcpy(&genrep, c->in.queue, sizeof(genrep));

    /* Compute 32-bit sequence number of this packet. */
    if((genrep.response_type & 0x7f) != XCB_KEYMAP_NOTIFY)
    {
        uint64_t lastread = c->in.request_read;
        c->in.request_read = (lastread & UINT64_C(0xffffffffffff0000)) | genrep.sequence;
        if(XCB_SEQUENCE_COMPARE(c->in.request_read, <, lastread))
            c->in.request_read += 0x10000;
        if(XCB_SEQUENCE_COMPARE(c->in.request_read, >, c->in.request_expected))
            c->in.request_expected = c->in.request_read;

        if(c->in.request_read != lastread)
        {
            if(c->in.current_reply)
            {
                _xcb_map_put(c->in.replies, lastread, c->in.current_reply);
                c->in.current_reply = 0;
                c->in.current_reply_tail = &c->in.current_reply;
            }
            c->in.request_completed = c->in.request_read - 1;
        }

        while(c->in.pending_replies && 
              c->in.pending_replies->workaround != WORKAROUND_EXTERNAL_SOCKET_OWNER &&
	      XCB_SEQUENCE_COMPARE (c->in.pending_replies->last_request, <=, c->in.request_completed))
        {
            pending_reply *oldpend = c->in.pending_replies;
            c->in.pending_replies = oldpend->next;
            if(!oldpend->next)
                c->in.pending_replies_tail = &c->in.pending_replies;
            free(oldpend);
        }

        if(genrep.response_type == XCB_ERROR)
            c->in.request_completed = c->in.request_read;
    }

    if(genrep.response_type == XCB_ERROR || genrep.response_type == XCB_REPLY)
    {
        pend = c->in.pending_replies;
        if(pend &&
           !(XCB_SEQUENCE_COMPARE(pend->first_request, <=, c->in.request_read) &&
             (pend->workaround == WORKAROUND_EXTERNAL_SOCKET_OWNER ||
              XCB_SEQUENCE_COMPARE(c->in.request_read, <=, pend->last_request))))
            pend = 0;
    }

    /* For reply packets, check that the entire packet is available. */
    if(genrep.response_type == XCB_REPLY)
    {
        if(pend && pend->workaround == WORKAROUND_GLX_GET_FB_CONFIGS_BUG)
        {
            uint32_t *p = (uint32_t *) c->in.queue;
            genrep.length = p[2] * p[3] * 2;
        }
        length += genrep.length * 4;
    }

    /* XGE events may have sizes > 32 */
    if (genrep.response_type == XCB_XGE_EVENT)
    {
        eventlength = ((xcb_ge_event_t*)&genrep)->length * 4;
    }

    bufsize = length + eventlength +
        (genrep.response_type == XCB_REPLY ? 0 : sizeof(uint32_t));
    if (bufsize < INT32_MAX)
        buf = malloc((size_t) bufsize);
    else
        buf = NULL;
    if(!buf)
    {
        _xcb_conn_shutdown(c);
        return 0;
    }

    if(_xcb_in_read_block(c, buf, length) <= 0)
    {
        free(buf);
        return 0;
    }

    /* pull in XGE event data if available, append after event struct */
    if (eventlength)
    {
        if(_xcb_in_read_block(c, &((xcb_generic_event_t*)buf)[1], eventlength) <= 0)
        {
            free(buf);
            return 0;
        }
    }

    if(pend && (pend->flags & XCB_REQUEST_DISCARD_REPLY))
    {
        free(buf);
        return 1;
    }

    if(genrep.response_type != XCB_REPLY)
        ((xcb_generic_event_t *) buf)->full_sequence = c->in.request_read;

    /* reply, or checked error */
    if( genrep.response_type == XCB_REPLY ||
       (genrep.response_type == XCB_ERROR && pend && (pend->flags & XCB_REQUEST_CHECKED)))
    {
        reader_list *reader;
        struct reply_list *cur = malloc(sizeof(struct reply_list));
        if(!cur)
        {
            _xcb_conn_shutdown(c);
            free(buf);
            return 0;
        }
        cur->reply = buf;
        cur->next = 0;
        *c->in.current_reply_tail = cur;
        c->in.current_reply_tail = &cur->next;
        for(reader = c->in.readers; 
	    reader && 
	    XCB_SEQUENCE_COMPARE_32(reader->request, <=, c->in.request_read);
	    reader = reader->next)
	{
            if(XCB_SEQUENCE_COMPARE_32(reader->request, ==, c->in.request_read))
            {
                pthread_cond_signal(reader->data);
                break;
            }
	}
        return 1;
    }

    /* event, or unchecked error */
    event = malloc(sizeof(struct event_list));
    if(!event)
    {
        _xcb_conn_shutdown(c);
        free(buf);
        return 0;
    }
    event->event = buf;
    event->next = 0;
    *c->in.events_tail = event;
    c->in.events_tail = &event->next;
    pthread_cond_signal(&c->in.event_cond);
    return 1; /* I have something for you... */
}

static xcb_generic_event_t *get_event(xcb_connection_t *c)
{
    struct event_list *cur = c->in.events;
    xcb_generic_event_t *ret;
    if(!c->in.events)
        return 0;
    ret = cur->event;
    c->in.events = cur->next;
    if(!cur->next)
        c->in.events_tail = &c->in.events;
    free(cur);
    return ret;
}

static void free_reply_list(struct reply_list *head)
{
    while(head)
    {
        struct reply_list *cur = head;
        head = cur->next;
        free(cur->reply);
        free(cur);
    }
}

static int read_block(const int fd, void *buf, const ssize_t len)
{
    int done = 0;
    while(done < len)
    {
        int ret = read(fd, ((char *) buf) + done, len - done);
        if(ret > 0)
            done += ret;
        if(ret < 0 && errno == EAGAIN)
        {
#if USE_POLL
            struct pollfd pfd;
            pfd.fd = fd;
            pfd.events = POLLIN;
            pfd.revents = 0;
            do {
                ret = poll(&pfd, 1, -1);
            } while (ret == -1 && errno == EINTR);
#else
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(fd, &fds);
	    do {
		ret = select(fd + 1, &fds, 0, 0, 0);
	    } while (ret == -1 && errno == EINTR);
#endif
        }
        if(ret <= 0)
            return ret;
    }
    return len;
}

static int poll_for_reply(xcb_connection_t *c, unsigned int request, void **reply, xcb_generic_error_t **error)
{
    struct reply_list *head;

    /* If an error occurred when issuing the request, fail immediately. */
    if(!request)
        head = 0;
    /* We've read requests past the one we want, so if it has replies we have
     * them all and they're in the replies map. */
    else if(XCB_SEQUENCE_COMPARE_32(request, <, c->in.request_read))
    {
        head = _xcb_map_remove(c->in.replies, request);
        if(head && head->next)
            _xcb_map_put(c->in.replies, request, head->next);
    }
    /* We're currently processing the responses to the request we want, and we
     * have a reply ready to return. So just return it without blocking. */
    else if(XCB_SEQUENCE_COMPARE_32(request, ==, c->in.request_read) && c->in.current_reply)
    {
        head = c->in.current_reply;
        c->in.current_reply = head->next;
        if(!head->next)
            c->in.current_reply_tail = &c->in.current_reply;
    }
    /* We know this request can't have any more replies, and we've already
     * established it doesn't have a reply now. Don't bother blocking. */
    else if(XCB_SEQUENCE_COMPARE_32(request, ==, c->in.request_completed))
        head = 0;
    /* We may have more replies on the way for this request: block until we're
     * sure. */
    else
        return 0;

    if(error)
        *error = 0;
    *reply = 0;

    if(head)
    {
        if(((xcb_generic_reply_t *) head->reply)->response_type == XCB_ERROR)
        {
            if(error)
                *error = head->reply;
            else
                free(head->reply);
        }
        else
            *reply = head->reply;

        free(head);
    }

    return 1;
}

/* Public interface */

void *xcb_wait_for_reply(xcb_connection_t *c, unsigned int request, xcb_generic_error_t **e)
{
    uint64_t widened_request;
    void *ret = 0;
    if(e)
        *e = 0;
    if(c->has_error)
        return 0;

    pthread_mutex_lock(&c->iolock);

    widened_request = (c->out.request & UINT64_C(0xffffffff00000000)) | request;
    if(widened_request > c->out.request)
        widened_request -= UINT64_C(1) << 32;

    /* If this request has not been written yet, write it. */
    if(c->out.return_socket || _xcb_out_flush_to(c, widened_request))
    {
        pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
        reader_list reader;
        reader_list **prev_reader;

        for(prev_reader = &c->in.readers; 
	    *prev_reader && 
	    XCB_SEQUENCE_COMPARE_32((*prev_reader)->request, <=, request);
	    prev_reader = &(*prev_reader)->next)
	{
            /* empty */;
	}
        reader.request = request;
        reader.data = &cond;
        reader.next = *prev_reader;
        *prev_reader = &reader;

        while(!poll_for_reply(c, request, &ret, e))
            if(!_xcb_conn_wait(c, &cond, 0, 0))
                break;

        for(prev_reader = &c->in.readers;
	    *prev_reader && 
	    XCB_SEQUENCE_COMPARE_32((*prev_reader)->request, <=, request);
	    prev_reader = &(*prev_reader)->next)
	{
            if(*prev_reader == &reader)
            {
                *prev_reader = (*prev_reader)->next;
                break;
            }
	}
        pthread_cond_destroy(&cond);
    }

    wake_up_next_reader(c);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

int xcb_poll_for_reply(xcb_connection_t *c, unsigned int request, void **reply, xcb_generic_error_t **error)
{
    int ret;
    if(c->has_error)
    {
        *reply = 0;
        if(error)
            *error = 0;
        return 1; /* would not block */
    }
    assert(reply != 0);
    pthread_mutex_lock(&c->iolock);
    ret = poll_for_reply(c, request, reply, error);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

xcb_generic_event_t *xcb_wait_for_event(xcb_connection_t *c)
{
    xcb_generic_event_t *ret;
    if(c->has_error)
        return 0;
    pthread_mutex_lock(&c->iolock);
    /* get_event returns 0 on empty list. */
    while(!(ret = get_event(c)))
        if(!_xcb_conn_wait(c, &c->in.event_cond, 0, 0))
            break;

    wake_up_next_reader(c);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

xcb_generic_event_t *xcb_poll_for_event(xcb_connection_t *c)
{
    xcb_generic_event_t *ret = 0;
    if(!c->has_error)
    {
        pthread_mutex_lock(&c->iolock);
        /* FIXME: follow X meets Z architecture changes. */
        ret = get_event(c);
        if(!ret && _xcb_in_read(c)) /* _xcb_in_read shuts down the connection on error */
            ret = get_event(c);
        pthread_mutex_unlock(&c->iolock);
    }
    return ret;
}

xcb_generic_error_t *xcb_request_check(xcb_connection_t *c, xcb_void_cookie_t cookie)
{
    /* FIXME: this could hold the lock to avoid syncing unnecessarily, but
     * that would require factoring the locking out of xcb_get_input_focus,
     * xcb_get_input_focus_reply, and xcb_wait_for_reply. */
    xcb_generic_error_t *ret;
    void *reply;
    if(c->has_error)
        return 0;
    if(XCB_SEQUENCE_COMPARE_32(cookie.sequence,>,c->in.request_expected)
       && XCB_SEQUENCE_COMPARE_32(cookie.sequence,>,c->in.request_completed))
    {
        free(xcb_get_input_focus_reply(c, xcb_get_input_focus(c), &ret));
        assert(!ret);
    }
    reply = xcb_wait_for_reply(c, cookie.sequence, &ret);
    assert(!reply);
    return ret;
}

/* Private interface */

int _xcb_in_init(_xcb_in *in)
{
    if(pthread_cond_init(&in->event_cond, 0))
        return 0;
    in->reading = 0;

    in->queue_len = 0;

    in->request_read = 0;
    in->request_completed = 0;

    in->replies = _xcb_map_new();
    if(!in->replies)
        return 0;

    in->current_reply_tail = &in->current_reply;
    in->events_tail = &in->events;
    in->pending_replies_tail = &in->pending_replies;

    return 1;
}

void _xcb_in_destroy(_xcb_in *in)
{
    pthread_cond_destroy(&in->event_cond);
    free_reply_list(in->current_reply);
    _xcb_map_delete(in->replies, (void (*)(void *)) free_reply_list);
    while(in->events)
    {
        struct event_list *e = in->events;
        in->events = e->next;
        free(e->event);
        free(e);
    }
    while(in->pending_replies)
    {
        pending_reply *pend = in->pending_replies;
        in->pending_replies = pend->next;
        free(pend);
    }
}

int _xcb_in_expect_reply(xcb_connection_t *c, uint64_t request, enum workarounds workaround, int flags)
{
    pending_reply *pend = malloc(sizeof(pending_reply));
    assert(workaround != WORKAROUND_NONE || flags != 0);
    if(!pend)
    {
        _xcb_conn_shutdown(c);
        return 0;
    }
    pend->first_request = pend->last_request = request;
    pend->workaround = workaround;
    pend->flags = flags;
    pend->next = 0;
    *c->in.pending_replies_tail = pend;
    c->in.pending_replies_tail = &pend->next;
    return 1;
}

void _xcb_in_replies_done(xcb_connection_t *c)
{
    struct pending_reply *pend;
    if (c->in.pending_replies_tail != &c->in.pending_replies)
    {
        pend = container_of(c->in.pending_replies_tail, struct pending_reply, next);
        if(pend->workaround == WORKAROUND_EXTERNAL_SOCKET_OWNER)
        {
            pend->last_request = c->out.request;
            pend->workaround = WORKAROUND_NONE;
        }
    }
}

int _xcb_in_read(xcb_connection_t *c)
{
    int n = read(c->fd, c->in.queue + c->in.queue_len, sizeof(c->in.queue) - c->in.queue_len);
    if(n > 0)
        c->in.queue_len += n;
    while(read_packet(c))
        /* empty */;
    if((n > 0) || (n < 0 && errno == EAGAIN))
        return 1;
    _xcb_conn_shutdown(c);
    return 0;
}

int _xcb_in_read_block(xcb_connection_t *c, void *buf, int len)
{
    int done = c->in.queue_len;
    if(len < done)
        done = len;

    memcpy(buf, c->in.queue, done);
    c->in.queue_len -= done;
    memmove(c->in.queue, c->in.queue + done, c->in.queue_len);

    if(len > done)
    {
        int ret = read_block(c->fd, (char *) buf + done, len - done);
        if(ret <= 0)
        {
            _xcb_conn_shutdown(c);
            return ret;
        }
    }

    return len;
}