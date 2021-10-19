CFLAGS=-Wall -std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) $(LDFLAGS)

build:
	docker build ./ -t mini-mini-pascal

rmi:
	docker rmi mini-mini-pascal

clean:
	rm -f main *.o *~

format:
	clang-format -style=google -i *.c *.h

.PHONY: clean format
