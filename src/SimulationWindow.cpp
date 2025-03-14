#include "SimulationWindow.hpp"

#include <cmath>
#include <iostream>

SimulationWindow::SimulationWindow(sf::Vector2f size, std::string name) {
    this->size = size;
    World world = World(ceil(size.x/renderScale.x), ceil(size.y/renderScale.y));
    world.randomizeStatus(0.5);
    this->simulator = Simulator(world);
    this->name = name;
}

void SimulationWindow::start() {
    
    // Window
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), name);
    window.setFramerateLimit(speed);
    World *world = simulator.getWorld();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Cell object to draw in alive cells
        sf::RectangleShape cell(sf::Vector2f(1,1));
        cell.setScale(renderScale);
        cell.setFillColor(sf::Color::White);

        for (size_t i=0; i < world->getHeight(); i++) {
            for (size_t j=0; j < world->getWidth(); j++) {

                if (!world->getCellStatus(j,i)) continue;
                sf::Vector2f newPosition;
                newPosition.x = j * renderScale.x;
                newPosition.y = i * renderScale.y;
                cell.setPosition(newPosition);
                window.draw(cell);
                
            }
        }

        window.display();
        simulator.nextTick();
    }

}