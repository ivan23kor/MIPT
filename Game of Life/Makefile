CXX := clang++ -v

OMP := -fopenmp
SFML := -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
LIBS := $(SFML)

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%,obj/%,$(SRC:.cpp=.o))
TARGET := game

all: create_obj_dir $(TARGET)

.PHONY: create_obj_dir
create_obj_dir:
	@mkdir -p obj

obj/%.o: src/%.cpp
	$(CXX) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $^ $(LIBS) -o $@

clean:
	$(RM) $(OBJ) $(TARGET)
