CC = g++
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BIN_DIR = ../bin

World.o: World.cpp World.hpp
	$(CC) -c $< -o $(BIN_DIR)/World.o

Simulator.o: Simulator.cpp Simulator.hpp
	$(CC) -c $< -o $(BIN_DIR)/Simulator.o

EXECUTABLE_NAME = main
MAIN_DEPENDENCIES = $(BIN_DIR)/$(EXECUTABLE_NAME).o $(BIN_DIR)/World.o $(BIN_DIR)/Simulator.o

$(EXECUTABLE_NAME).o: $(EXECUTABLE_NAME).cpp
	$(CC) -c $< -o $(BIN_DIR)/$(EXECUTABLE_NAME).o

$(EXECUTABLE_NAME): World.o Simulator.o $(EXECUTABLE_NAME).o
	$(CC) $(MAIN_DEPENDENCIES) -o $(BIN_DIR)/$(EXECUTABLE_NAME) $(SFML_FLAGS)

clear:
	rm $(BIN_DIR)/*.o $(BIN_DIR)/$(EXECUTABLE_NAME)

run: $(EXECUTABLE_NAME)
	$(BIN_DIR)/$(EXECUTABLE_NAME)

all: run