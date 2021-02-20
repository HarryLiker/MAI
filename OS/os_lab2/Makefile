all: parent.out child.out

parent.out: parent.c
	gcc parent.c -o parent.out

child.out: child.c
	gcc child.c -o child.out

clean:
	rm *.out