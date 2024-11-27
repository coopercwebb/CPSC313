CFLAGS = -Wall -g

all: test

catch.o: catch.cpp catch.hpp
	g++ -g -std=c++11 -o catch.o -c catch.cpp

test: catch.o lbnToPbn.o test.cpp
	g++ -g -std=c++11 -o test catch.o test.cpp lbnToPbn.o

lbnToPbn.o: lbnToPbn.c lbnToPbn.h
	gcc -g $(CFLAGS) -o lbnToPbn.o -c lbnToPbn.c

clean:
	rm -rf lbnToPbn.o test

tidy:
	rm -rf *.o test