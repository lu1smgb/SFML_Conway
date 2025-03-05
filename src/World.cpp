#include "World.hpp"

#include <iostream>
#include <random>
#include <limits>

#define BORDER_THICKNESS 2

bool validIndexes(World *world, size_t row, size_t column) {
    const size_t rows = world->getHeight(), columns = world->getWidth();
    if (row < 0 || row >= rows || rows == 0 || column < 0 || column >= columns || columns == 0) return false;
    return true;
}

bool validSize(size_t size) {
    return size > 0 && size <= UINT64_MAX-1;
}

World::World(size_t width, size_t height, float cellScale) {
    // Allocate rows
    if (!validSize(height) || !validSize(width)) {
        throw std::invalid_argument("Non-valid size parameter on world constructor");
    }
    this->grid.resize(height);
    for (size_t i = 0; i < this->getHeight(); i++) {
        // Allocate column cells for the row
        this->grid[i].resize(width);
        for (size_t j = 0; j < this->getWidth(); j++) {
            // Compute display position
            float x = pow(cellScale, 2)*j;
            float y = pow(cellScale, 2)*i;
            sf::Vector2f cellPosition(x,y);
            // Create cell instance
            this->grid[i][j] = Cell(cellPosition, false, cellScale, sf::Color::White);
        }
    }
    sf::Vector2f borderSize(this->getWidth() * pow(cellScale, 2), this->getHeight() * pow(cellScale, 2));
    this->border = sf::RectangleShape(borderSize);
    this->border.setFillColor(sf::Color(0,0,0,0));
    this->border.setOutlineThickness(BORDER_THICKNESS);
    this->border.setOutlineColor(sf::Color::Red);
}

void World::setCellStatus(size_t row, size_t column, bool newStatus) {
    if (!validIndexes(this, row, column)) return;
    return this->grid[row][column].setStatus(newStatus);
}

inline bool World::getCellStatus(size_t row, size_t column) {
    if (!validIndexes(this, row, column)) return false;
    return this->grid[row][column].getStatus();
}

inline size_t World::getWidth() const {
    if (this->getHeight() <= 0) return 0;
    return this->grid[0].size();
}

inline void World::setWidth(size_t width) {
    if (!validSize(width)) {
        throw std::invalid_argument("Non-valid width value on setter");
    }
    for (CellRow_t row: this->grid) {
        row.resize(width);
    }
}

inline size_t World::getHeight() const {
    return this->grid.size();
}

inline void World::setHeight(size_t height) {
    if (!validSize(height)) {
        throw std::invalid_argument("Non-valid height value on setter");
    }
    this->grid.resize(height);
}

void World::setOffset(float x, float y) {
    // Translate cells
    for (size_t i = 0; i < this->getHeight(); i++) {
        for (size_t j = 0; j < this->getWidth(); j++) {
            Cell *c = &(this->grid[i][j]);
            sf::Vector2f newPosition(c->getPosition());
            newPosition.x += x; newPosition.y += y;
            c->setPosition(newPosition);
        }
    }
    // Translate border
    sf::Vector2f newPosition(this->border.getPosition());
    newPosition.x += x; newPosition.y += y;
    this->border.setPosition(newPosition);
}

void World::setOffset(sf::Vector2f vec) {
    this->setOffset(vec.x, vec.y);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (CellRow_t row: this->grid) {
        for (Cell c: row) target.draw(c, states);
    }
    target.draw(this->border, states);
}

void World::randomizeStatus(float alivePercentage = 0.5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for (size_t i = 0; i < this->getHeight(); i++) {
        for (size_t j = 0; j < this->getWidth(); j++) {
            float randVal = dis(gen);
            this->grid[i][j].setStatus(randVal > alivePercentage);
        }
    }
}