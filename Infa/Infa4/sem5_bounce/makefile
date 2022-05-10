PROJECT_NAME = bounce

$(PROJECT_NAME) : main.o figures.o vector2.o
	g++ -o $(PROJECT_NAME) main.o figures.o vector2.o -std=c++11 -lm -lsfml-graphics -lsfml-window -lsfml-system
main.o :
	g++ -c main.cpp
figures.o :
	g++ -c figures.cpp
vector2.o :
	g++ -c vector2.cpp 
clean :
	rm -f *.o $(PROJECT_NAME) *~