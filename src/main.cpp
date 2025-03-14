#include "SimulationWindow.hpp"

int main() {
    SimulationWindow window(sf::Vector2f(1280, 720), "SFML Conway");
    window.start();
}