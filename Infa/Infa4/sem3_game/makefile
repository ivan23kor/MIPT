PROJECT_NAME = game

$(PROJECT_NAME) : main.o logic.o graphics.o vector2.o
	g++ main.o logic.o graphics.o vector2.o -o $(PROJECT_NAME) -lm -lsfml-graphics -lsfml-window -lsfml-system
main.o :
	g++ -c main.cpp
logic.o :
	g++ -c logic.cpp
graphics.o :
	g++ -c graphics.cpp
vector2.o :
	g++ -c vector2.cpp
move :
	g++ move.cpp -o move -lm -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -f *.o $(PROJECT_NAME) *~