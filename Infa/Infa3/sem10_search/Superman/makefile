superman: superman.o stack.o
	gcc superman.o stack.o -o superman
superman.o: superman.c
	gcc -c superman.c -o superman.o
stack.o: stack.c
	gcc -c stack.c -o stack.o

clean:
	rm *.o
	rm superman
	clear