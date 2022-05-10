main: main.o exec.o
	gcc main.o exec.o -o main
exec.o: exec.c exec.h
	gcc -c exec.c
main.o: main.c exec.h
	gcc -c main.c
clean:
	rm *.o
	rm main
