DEBUG = 1

CC = gcc
COMMON = -I./
CFLAGS =  -Wall
LDFLAGS = -L/usr/local
LDLIBS = -lmseed

SRCS := $(sort $(wildcard *.c))
OBJS := $(SRCS:%.c=%.o)

ifeq ($(DEBUG), 1)
CFLAGS += -O0 -g -DDEBUG=1
endif

.PHONY: all clean tests

all: $(OBJS)

tests: $(OBJS)
	@$(MAKE) -C tests

%.o: %.c
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C tests clean
