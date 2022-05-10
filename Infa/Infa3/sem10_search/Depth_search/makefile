search: search.o stack.o
	gcc search.o stack.o -o search
search.o: search.c
	gcc -c search.c -o search.o
stack.o: stack.c
	gcc -c stack.c -o stack.o

clean:
	rm *.o
	rm search