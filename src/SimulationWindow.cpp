#include "SimulationWindow.hpp"

#include <cmath>
#include <iostream>

SimulationWindow::SimulationWindow(sf::Vector2f size, std::string name) {
    this->size = size;
    double sizeX = ceil(size.x/renderScale), sizeY = ceil(size.y/renderScale);
    World world = World(sizeX, sizeY);
    world.randomizeStatus(0.5);
    this->simulator = Simulator(world);
    this->name = name;
}

void SimulationWindow::start() {
    
    // Window
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), name);
    window.setFramerateLimit(speed);
    window.setKeyRepeatEnabled(false);
    World *world = simulator.getWorld();

    // Font and color for counter displays
    sf::Font counterFont;
    if (!counterFont.loadFromFile("../fonts/DepartureMonoNerdFontPropo-Regular.otf")) {
        std::cerr << "Font could not be loaded" << std::endl;
        return;
    }
    sf::Color counterColor(0, 255, 255);
    unsigned int counterCharSize = 30;

    // Counter displays for generation and population
    sf::Text generationCounter, populationCounter;
    generationCounter.setFont(counterFont); 
    populationCounter.setFont(counterFont);
    generationCounter.setFillColor(counterColor); 
    populationCounter.setFillColor(counterColor);
    populationCounter.setOutlineThickness(2);
    generationCounter.setOutlineThickness(2);
    populationCounter.setOutlineColor(sf::Color::Black);
    generationCounter.setOutlineColor(sf::Color::Black);
    generationCounter.setCharacterSize(counterCharSize); 
    populationCounter.setCharacterSize(counterCharSize);
    generationCounter.setPosition(sf::Vector2f(8, size.y - counterCharSize - 8)); 
    populationCounter.setPosition(sf::Vector2f(8, size.y - counterCharSize * 2 - 8));

    // Display for simulator status (running, paused)
    sf::Font runningFont;
    if (!runningFont.loadFromFile("../fonts/BigBlueTerm437NerdFontPropo-Regular.ttf")) {
        std::cerr << "Font could not be loaded" << std::endl;
        return;
    }
    sf::Text runningDisplay;
    runningDisplay.setFont(runningFont);
    runningDisplay.setFillColor(sf::Color::Red);
    runningDisplay.setOutlineThickness(2);
    runningDisplay.setOutlineColor(sf::Color::Black);
    runningDisplay.setCharacterSize(counterCharSize);
    runningDisplay.setPosition(sf::Vector2f(8, size.y - counterCharSize * 3 - 8));

    while (window.isOpen()) {
        
        // Window event managing
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed and sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                simulator.isRunning() ? simulator.pause() : simulator.resume();
            }
            if (focus && event.type == sf::Event::LostFocus and simulator.isRunning()) {
                simulator.pause();
                focus = false;
            }
            if (!focus && event.type == sf::Event::GainedFocus and !simulator.isRunning()) {
                simulator.resume();
                focus = true;
            }
        }

        // Clear
        window.clear(sf::Color::Black);

        // Cell object to draw in alive cells
        sf::RectangleShape cell(sf::Vector2f(1,1));
        cell.setScale(sf::Vector2f(renderScale, renderScale));
        cell.setFillColor(sf::Color::White);

        // Draw alive cells
        for (size_t i=0; i < world->getHeight(); i++) {
            for (size_t j=0; j < world->getWidth(); j++) {

                if (!world->getCellStatus(i,j)) continue;
                sf::Vector2f newPosition;
                newPosition.x = j * renderScale;
                newPosition.y = i * renderScale;
                cell.setPosition(newPosition);
                window.draw(cell);
                
            }
        }

        // Display generation and population
        generationCounter.setString("Generation:" + std::to_string(simulator.getGenerationNumber()));
        populationCounter.setString("Population:" + std::to_string(world->getPopulation()));        
        window.draw(generationCounter);
        window.draw(populationCounter);

        // Running display
        if (simulator.isRunning()) {
            runningDisplay.setString("Running");
            runningDisplay.setFillColor(sf::Color::Green);
        }
        else {
            runningDisplay.setString("Paused");
            runningDisplay.setFillColor(sf::Color::Red);
        }
        window.draw(runningDisplay);

        // Render objects
        window.display();

        // Get to the next generation
        simulator.nextTick();
    }

}