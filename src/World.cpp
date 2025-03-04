#include "World.hpp"

#include <iostream>
#include <random>

World::World(size_t width, size_t height, float cellScale) {
    this->grid.resize(height);
    for (size_t i = 0; i < height; i++) {
        this->grid[i].resize(width);
        for (size_t j = 0; j < width; j++) {
            // Compute display position
            float x = cellScale*cellScale*j;
            float y = cellScale*cellScale*i;
            sf::Vector2f cellPosition(x,y);
            // Create cell instance
            this->grid[i][j] = Cell(cellPosition, true, cellScale, sf::Color::White);
        }
    }
}

inline void World::setCellStatus(size_t row, size_t column, bool newStatus) {
    this->grid[row][column].setStatus(newStatus);
}

inline bool World::getCellStatus(size_t row, size_t column) const {
    return this->grid[row][column].getStatus();
}

void World::setOffset(float x, float y) {
    for (size_t i = 0; i < this->grid.size(); i++) {
        for (size_t j = 0; j < this->grid.at(0).size(); j++) {
            Cell *c = &(this->grid[i][j]);
            sf::Vector2f actualPosition = c->getPosition();
            sf::Vector2f newPosition(actualPosition);
            newPosition.x += x;
            newPosition.y += y;
            this->grid[i][j].setPosition(newPosition);
        }
    }
}

void World::setOffset(sf::Vector2f vec) {
    this->setOffset(vec.x, vec.y);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (CellRow_t row: this->grid) {
        for (Cell c: row) {
            target.draw(c, states);
        }
    }
}

void World::randomizeStatus(float alivePercentage = 0.5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (size_t i = 0; i < this->grid.size(); i++) {
        for (size_t j = 0; j < this->grid.at(0).size(); j++) {
            Cell *c = &this->grid[i][j];
            float randVal = dis(gen);
            c->setStatus(randVal > alivePercentage);
        }
    }
}