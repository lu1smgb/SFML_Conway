#include <iostream>

#include <SFML/Graphics.hpp>

#include "World.hpp"

int main() {
    sf::Vector2u resolution(1280, 720);
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Ventana!");
    window.setFramerateLimit(10);

    // Font
    std::string fontPath = "../fonts/";
    std::string fontFile = "DepartureMonoNerdFontPropo-Regular.otf";
    fontPath.append(fontFile);
    sf::Font textFont;
    if (!textFont.loadFromFile(fontPath)) {
        std::cerr << "ERROR: La fuente no se ha podido cargar" << std::endl;
        return -1;
    }

    // Text
    unsigned int counter = 0;
    sf::Text counterDisplay(std::to_string(counter), textFont, 24);
    counterDisplay.setFillColor(sf::Color::Cyan);

    // Cell
    // Cell c1 = Cell(sf::Vector2f(120,120), true, 6, sf::Color::White);
    // Cell c2 = Cell(sf::Vector2f(160,120), true, 6, sf::Color::Green);

    // World
    World w = World(60, 40, 4);
    w.randomizeStatus(0.5);
    // w.setCellStatus(0,  0,  true);
    // w.setCellStatus(10, 20, true);
    // w.setCellStatus(9,  19, true);
    // w.setCellStatus(11, 19, true);
    // w.setCellStatus(10, 18, true);
    w.setOffset(sf::Vector2f(50, 50));

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(w);
        window.draw(counterDisplay);
        window.display();
        counter++;
        counterDisplay.setString(std::to_string(counter));

    }
}