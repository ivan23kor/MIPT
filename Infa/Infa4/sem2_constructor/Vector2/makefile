CC = g++
CO = $(CC) -c
EXE = app
LIB = vector2

$(EXE) : main.o $(LIB).o
	$(CC) main.o $(LIB).o -o $(EXE)
main.o : main.cpp
	$(CO) main.cpp
$(LIB).o : $(LIB).cpp
	$(CO) $(LIB).cpp
clean:
	rm -f *.o *~ app