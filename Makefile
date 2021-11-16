CXX=g++
CXXFLAGS=-Wall -O2 -std=c++17 -g -static
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS) $(LDFLAGS)

build:
	docker build ./ -t mini-mini-pascal
	docker run --rm -v $(HOME)/Develop/Mini-Mini-Pascal:/Mini-Mini-Pascal -w /Mini-Mini-Pascal mini-mini-pascal make

run: build
	docker run --rm -v $(HOME)/Develop/Mini-Mini-Pascal:/Mini-Mini-Pascal -w /Mini-Mini-Pascal mini-mini-pascal ./main ${ARG}

rmi:
	docker rmi mini-mini-pascal

clean:
	rm -f main *.o *~

format:
	clang-format -style=google -i *.cpp *.h

.PHONY: build run rmi clean format
