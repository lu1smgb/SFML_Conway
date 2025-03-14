#include "World.hpp"

#include <iostream>
#include <random>
#include <climits>

#define BORDER_THICKNESS 2

bool World::validIndexes(size_t row, size_t column) const {
    size_t width = getWidth(), height = getHeight();
    return !(row < 0 || row >= height || height == 0 || column < 0 || column >= width || width == 0);
}

bool World::validSize(size_t size) const {
    return size > 0 && size <= ULONG_MAX;
}

bool World::validDimensions(size_t width, size_t height) const {
    return validSize(width) && validSize(height);
}

World::World() {}

World::World(const World& other) {
    this->width = other.width;
    this->height = other.height;
    this->population = other.population;
    this->grid = other.grid;
}

World::World(size_t width, size_t height) {
    // Allocate rows
    if (!validDimensions(width, height)) {
        throw std::invalid_argument("Non-valid size parameter on world constructor");
    }
    this->width = width;
    this->height = height;
    grid = CellGrid_t(height, CellRow_t(width, false));
}

void World::setCellStatus(size_t row, size_t column, bool newStatus) {
    if (!validIndexes(row, column)) return;
    grid[row][column] = newStatus;
    population += newStatus ? 1 : -1; // TODO: Problemas de overflow
}

bool World::getCellStatus(size_t row, size_t column) const {
    if (!validIndexes(row, column)) return false;
    return this->grid.at(row).at(column);
}

void World::kill(size_t row, size_t column) {
    setCellStatus(row, column, false);
}

void World::birth(size_t row, size_t column) {
    setCellStatus(row, column, true);
}   

size_t World::getWidth() const {
    return width;
}

size_t World::getHeight() const {
    return height;
}

unsigned long World::getPopulation() const {
    return population;
}

void World::randomizeStatus(float alivePercentage = 0.5) {
    // Setting up generator objects
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (size_t i = 0; i < this->getHeight(); i++) {
        for (size_t j = 0; j < this->getWidth(); j++) {
            float randVal = dis(gen);
            setCellStatus(j, i, randVal > alivePercentage);
        }
    }
}