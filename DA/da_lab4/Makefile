CC=g++

CFLAGS=--std=c++17 -Wall -c -O3
FLAGS_GPROF = -std=c++17 -pg
FLAGS_O3 = -std=c++17 -O3

all: solution

solution: main.o search.o
	$(CC) main.o search.o -o solution 

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

search.o: search.cpp
	$(CC) $(CFLAGS) search.cpp

clean:
	rm -rf *.o solution