exe: Poem.o Func.o
	gcc Poem.o Func.o -lm -o exe
Poem.o: Poem.c Poem.h
	gcc -c Poem.c
Func.o: Func.c Poem.h
	gcc -c Func.c
clean:
	rm *.o
	rm exe