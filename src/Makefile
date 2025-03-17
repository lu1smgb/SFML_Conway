CC = g++
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BIN_DIR = ../bin

World.o: World.cpp World.hpp
	$(CC) -c $< -o $(BIN_DIR)/World.o

Simulator.o: Simulator.cpp Simulator.hpp
	$(CC) -c $< -o $(BIN_DIR)/Simulator.o

SimulationWindow.o: SimulationWindow.cpp SimulationWindow.hpp
	$(CC) -c $< -o $(BIN_DIR)/SimulationWindow.o

EXE_NAME = main
EXE_DEPENDENCIES = $(BIN_DIR)/$(EXE_NAME).o $(BIN_DIR)/World.o $(BIN_DIR)/Simulator.o $(BIN_DIR)/SimulationWindow.o

$(BIN_DIR)/$(EXE_NAME).o: $(EXE_NAME).cpp
	$(CC) -c $< -o $(BIN_DIR)/$(EXE_NAME).o

$(EXE_NAME): $(BIN_DIR)/main.o World.o Simulator.o SimulationWindow.o
	$(CC) $(EXE_DEPENDENCIES) -o $(BIN_DIR)/$(EXE_NAME) $(SFML_FLAGS)

clear:
	rm $(BIN_DIR)/*.o

run: $(EXE_NAME)
	$(BIN_DIR)/$(EXE_NAME)

all: run