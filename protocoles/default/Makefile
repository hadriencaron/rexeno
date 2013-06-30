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

CFLAGS=$(shell $(XENOCONFIG) --xeno-cflags) $(MY_CFLAGS) -lnative -lanalogy -lrtdm

LDFLAGS=$(shell $(XENOCONFIG) --xeno-ldflags) $(MY_LDFLAGS)

# This includes the library path of given Xenomai into the binary to make live
# easier for beginners if Xenomai's libs are not in any default search path.
LDFLAGS+=-Xlinker -rpath -Xlinker $(shell $(XENOCONFIG) --libdir)  \
	-lm -lX11 -g -ggdb
#LDFLAGS+=-lsession


all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) core *~

$(TARGET) : $(OBJS)
	g++ $(SRCS) -o $(TARGET) /usr/lib/libsession.a /usr/lib/librecorder.a /usr/lib/libdriver.a /usr/lib/libconfiguration.a -lGL -lboost_program_options -lglut $(CFLAGS) $(LDFLAGS)

noxeno:
	g++ $(SRCS) -o $(TARGET) /usr/lib/libsession.a /usr/lib/librecorder.a /usr/lib/libdriver.a /usr/lib/libconfiguration.a -lGL -lboost_program_options -lglut 
