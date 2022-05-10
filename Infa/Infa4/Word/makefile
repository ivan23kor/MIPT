CC = g++ -std=c++11
CO = $(CC) -c
EXE = app
LIB = word

$(EXE) : main.o $(LIB).o
	$(CC) main.o $(LIB).o -o $(EXE)
main.o : main.cpp word.h
	$(CO) main.cpp
$(LIB).o : $(LIB).cpp word.h
	$(CO) $(LIB).cpp
clean:
	rm -f *.o $(EXE)