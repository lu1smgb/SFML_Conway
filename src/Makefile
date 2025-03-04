CC = g++
SFML_GRAPHICS = -lsfml-graphics
SFML_WINDOW = -lsfml-window
SFML_SYSTEM = -lsfml-system
SFML_COMPILE_FLAGS = $(SFML_GRAPHICS) $(SFML_WINDOW) $(SFML_SYSTEM)

BIN_DIR = ../bin

Cell.o: Cell.cpp Cell.hpp 
	$(CC) -c $< -o $(BIN_DIR)/Cell.o

World.o: World.cpp World.hpp
	$(CC) -c $< -o $(BIN_DIR)/World.o

EXECUTABLE_NAME = main
MAIN_DEPENDENCIES = $(wildcard $(BIN_DIR)/*.o)

main.o: main.cpp
	$(CC) -c $< -o $(BIN_DIR)/main.o

main: World.o Cell.o main.o
	$(CC) $(MAIN_DEPENDENCIES) -o $(EXECUTABLE_NAME) $(SFML_COMPILE_FLAGS)

clear:
	rm $(BIN_DIR)/*.o

run: main
	./$(EXECUTABLE_NAME)

all: main