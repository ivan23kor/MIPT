PROJECT_NAME = kmeans

$(PROJECT_NAME) : main.o centroids.o
	g++ main.o centroids.o -o $(PROJECT_NAME) -lm -lsfml-graphics -lsfml-window -lsfml-system -std=c++11
main.o :
	g++ -c main.cpp
centroids.o :
	g++ -c centroids.cpp
clean:
	rm -f *.o $(PROJECT_NAME) *~