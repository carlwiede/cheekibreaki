SRC_DIR := ./src

ARGS := -g -std=c++17 $(SRC_DIR)/*.cpp $(SRC_DIR)/glad.c -lglfw -o program

build:
	g++ $(ARGS)

make clean:
	rm program
