#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "World.hpp"
#include <queue>
#include <memory>

class Simulator {
protected:
    World world;
    unsigned long gen = 0;
    bool paused = true;
    unsigned short getAliveNeighbours(size_t row, size_t column) const;
public:
    Simulator();
    Simulator(World world);
    void nextTick();
    World* getWorld();
    void pause();
    void resume();
    bool isRunning() const;
    unsigned long getGenerationNumber() const;
    unsigned long getWorldPopulation() const;
};

#endif