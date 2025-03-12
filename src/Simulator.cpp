#include "Simulator.hpp"

unsigned short Simulator::getAliveNeighbours(size_t row, size_t column) const {
    unsigned short counter = 0;
    for (char i = -1; i <= 1; i++) {
        for (char j = -1; j <= 1; j++) {
            if (i == 0 and j == 0) continue;
            if (world.getCellStatus(row+i, column+j)) counter++;
        }
    }
    return counter;
}

Simulator::Simulator(World &world)
{
    this->world = world;
}

void Simulator::nextTick() {
    World nextTickWorld(world.getWidth(), world.getHeight());
    for (size_t i = 0; i < world.getHeight(); i++) {
        for (size_t j = 0; j < world.getWidth(); j++) {
            unsigned short neighbours = getAliveNeighbours(i,j);
            bool alive = world.getCellStatus(i,j);
            if (alive and (neighbours < 2 or neighbours > 3)) nextTickWorld.kill(i,j);
            else if (!alive and neighbours == 3) nextTickWorld.birth(i,j);
            else nextTickWorld.setCellStatus(i,j,alive);
        }
    }
    world = nextTickWorld;
    gen++;
}

unsigned long Simulator::getGenerationNumber() const {
    return gen;
}

void Simulator::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(world, states);
}