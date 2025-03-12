#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "World.hpp"
#include <queue>
#include <memory>

class Simulator : public sf::Drawable {
protected:
    World world;
    unsigned long gen = 0;
    unsigned short getAliveNeighbours(size_t row, size_t column) const;
public:
    Simulator(World& world);
    void nextTick();
    unsigned long getGenerationNumber() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif