#ifndef SIMULATIONWINDOW_HPP
#define SIMULATIONWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "Simulator.hpp"

class SimulationWindow {
protected:
    Simulator simulator;
    sf::Vector2f size;
    unsigned long speed = 20;
    float renderScale = 4; 
    std::string name = "SimulationWindow";
public:
    SimulationWindow(sf::Vector2f size, std::string name);
    void start();
};

#endif