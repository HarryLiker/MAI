all: control comands

control:
	g++ control.cpp -lzmq -o control -Wall -pedantic

comands:
	g++ count.cpp -lzmq -o count -Wall -pedantic

clean:
	rm -rf control count