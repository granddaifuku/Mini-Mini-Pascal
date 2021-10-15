CC=gcc
CFLAGS=-Wall -std=c11 -g
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) $(LDFLAGS)

clean:
	rm -f main *.o *~

format:
	clang-format -style=google -i *.c *.h

.PHONY: clean format
