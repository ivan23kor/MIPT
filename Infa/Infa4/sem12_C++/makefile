CLASS_NAME = string

$(CLASS_NAME) : $(CLASS_NAME).o main.o
	g++ -o $(CLASS_NAME) $(CLASS_NAME).o main.o
&(CLASS_NAME).o : &(CLASS_NAME).cpp
	g++ -c $(CLASS_NAME).cpp
main.o : main.cpp
	g++ -c main.cpp
clean :
	rm -f *.o *~ $(CLASS_NAME)