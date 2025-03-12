#include <iostream>

#include <SFML/Graphics.hpp>
#include <cmath>

#include "World.hpp"
#include "Simulator.hpp"

int main() {
    sf::Vector2u resolution(800, 800);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Ventana!");
    window.setFramerateLimit(2);

    // Font
    std::string fontPath = "../fonts/";
    std::string fontFile = "DepartureMonoNerdFontPropo-Regular.otf";
    fontPath.append(fontFile);
    sf::Font textFont;
    if (!textFont.loadFromFile(fontPath)) {
        std::cerr << "ERROR: La fuente no se ha podido cargar" << std::endl;
        return -1;
    }

    // World
    World world(200,200);
    // world.setCellStatus( ceil(world.getHeight() / 2), ceil(world.getWidth() / 2), true);
    // world.setCellStatus( ceil(world.getHeight() / 2)-1, ceil(world.getWidth() / 2), true);
    // world.setCellStatus( ceil(world.getHeight() / 2)-2, ceil(world.getWidth() / 2), true);
    world.randomizeStatus(0.5);

    // Simulator
    Simulator sim(world);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sim);
        window.display();

        sim.nextTick();

    }
}