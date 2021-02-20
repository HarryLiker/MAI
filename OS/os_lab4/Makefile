all: parent.out child.out

parent.out: parent.c shrmem.h
	gcc parent.c -o parent.out -lpthread -lrt

child.out: child.c shrmem.h
	gcc child.c -o child.out -lpthread -lrt

clean:
	rm *.out