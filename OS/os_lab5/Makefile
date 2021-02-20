all: function1 function2

function1: lib1.so
	gcc function1.c -L/root/work/MAI/OS/os_lab5 -l1 -Wall -o function1

function2: lib1.so lib2.so
	gcc function2.c -ldl -o function2

lib1.so: lib1.o
	gcc lib1.o -lm -shared -o lib1.so

lib1.o:
	gcc lib1.c -c -Wall -Werror -fpic -o lib1.o

lib2.so: lib2.o
	gcc lib2.o -shared -o lib2.so

lib2.o:
	gcc lib2.c -c -Wall -Werror -fpic -o lib2.o

clean:
	rm -rf *.so *.o function1 function2