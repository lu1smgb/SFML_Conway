#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector<bool> CellRow_t;
typedef std::vector<CellRow_t> CellGrid_t;

class World {
private:
    bool validIndexes(size_t row, size_t column) const;
    bool validSize(size_t size) const;
    bool validDimensions(size_t width, size_t height) const;
protected:
    size_t width, height;
    unsigned long population = 0;
    CellGrid_t grid;
public:
    World();
    World(const World& other);
    World(size_t width, size_t height);
    bool getCellStatus(size_t row, size_t column) const;
    void setCellStatus(size_t row, size_t column, bool newStatus);
    void kill(size_t row, size_t column);
    void birth(size_t row, size_t column);
    size_t getWidth() const;
    size_t getHeight() const;
    unsigned long getPopulation() const;
    void syncPopulation();
    void randomizeStatus(float alivePercentage);
};

#endif