CC=g++

CFLAGS=--std=c++17 -Wall -c -O3
FLAGS_GPROF = -std=c++17 -pg
FLAGS_O3 = -std=c++17 -O3

all: solution

solution: main.o functions.o menu.o
	$(CC) $(FLAGS_GPROF) main.o functions.o menu.o -o solution 

main.o: main.cpp
	$(CC) $(CFLAGS) $(FLAGS_GPROF) main.cpp

functions.o: functions.cpp
	$(CC) $(CFLAGS) $(FLAGS_GPROF) functions.cpp

menu.o: menu.cpp
	$(CC) $(CFLAGS) $(FLAGS_GPROF) menu.cpp

clean:
	rm -rf *.o solution

