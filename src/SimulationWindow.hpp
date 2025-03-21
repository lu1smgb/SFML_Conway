#ifndef SIMULATIONWINDOW_HPP
#define SIMULATIONWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "Simulator.hpp"

class SimulationWindow {
protected:
    Simulator simulator;
    sf::Vector2f size;
    unsigned long speed = 60;
    float renderScale = 8;
    bool focus = true;
    std::string name = "SimulationWindow";
public:
    SimulationWindow(sf::Vector2f size, std::string name);
    void start();
};

#endif