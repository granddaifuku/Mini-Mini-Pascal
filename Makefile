CC=gcc
CFLAGS=-std=c11 -g -static -Wall 
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

clean:
	rm -f main *.o *~

format:
	clang-format -style=file -i *.c *.h

.PHONY: clean format
