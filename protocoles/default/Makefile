SHELL = /bin/sh

TARGET = display

SRCS = main.cc

CC=g++

CDEBUG = -g
LDFLAGS += -g

CFLAGS += $(CDEBUG)



### Default Xenomai installation path
XENO ?= /usr/xenomai

XENOCONFIG=$(shell PATH=$(XENO):$(XENO)/bin:$(PATH) which xeno-config 2>/dev/null)



### Sanity check
ifeq ($(XENOCONFIG),)
all::
	@echo ">>> Invoke make like this: \"make XENO=/path/to/xeno-config\" <<<"
	@echo
endif


CC=$(shell $(XENOCONFIG) --cc) -ldl

CFLAGS=$(shell $(XENOCONFIG) --xeno-cflags) $(MY_CFLAGS)

LDFLAGS=$(shell $(XENOCONFIG) --xeno-ldflags) $(MY_LDFLAGS) -lnative

# This includes the library path of given Xenomai into the binary to make live
# easier for beginners if Xenomai's libs are not in any default search path.
# LDFLAGS+=-Xlinker -rpath -Xlinker $(shell $(XENOCONFIG) --libdir)  \
# 	-lglui -lrwconf -lm -lX11 -lXenoTimer -g -ggdb -lRecorder -lInterface -lPipeWriter
LDFLAGS+=-lsession


all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) core *~

$(TARGET) : $(OBJS)
	$(CC)  $(CFLAGS) $(LDFLAGS) $(SRCS) $(LIBFLAGS)  -ldisplayer -o $(TARGET)
