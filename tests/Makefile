DEBUG = 1
CC = gcc
CFLAGS = 
COMMON += -I../

LDFLAGS = -L/usr/local
LDLIBS = -lmseed

SRCS := $(sort $(wildcard *.c))
BINS := $(SRCS:%.c=%)
OBJS := $(sort $(wildcard ../*.o))

ifeq ($(DEBUG), 1)
CFLAGS += -O0 -g -DDEBUG=1
endif

.PHONY: all clean

all: $(BINS)

$(BINS): % : %.c
	@printf 'Building $<\n';
	$(CC) $(COMMON) $(CFLAGS) -o $@ $< $(OBJS) $(LDFLAGS) $(LDLIBS)

clean: 
	@rm -rf *.o $(BINS) *.dSYM
