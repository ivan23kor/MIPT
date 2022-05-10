EXE = move

move : move.o
	g++ move.o -o $(EXE) -lm -lsfml-graphics -lsfml-window -lsfml-system
move.o :
	g++ -c move.cpp
clean:
	rm -f *.o $(EXE) *~