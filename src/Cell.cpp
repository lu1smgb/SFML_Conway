#include "Cell.hpp"

Cell::Cell() {}

Cell::Cell(sf::Vector2f position = sf::Vector2f(0.f,0.f), bool status = false, unsigned short int scale = 1, sf::Color color = sf::Color::White) {
    this->shape = sf::RectangleShape(sf::Vector2f(scale, scale));
    this->setPosition(position);
    this->setScale(scale);
    this->setColor(color);
    this->setStatus(status);
}

void Cell::setPosition(sf::Vector2f position) {
    this->shape.setPosition(position);
}

void Cell::setScale(unsigned short int scale) {
    this->shape.setScale(sf::Vector2f(scale, scale));
}

void Cell::setColor(sf::Color color) {
    this->shape.setFillColor(color);
}

void Cell::setStatus(bool status) {
    this->status = status;
}

bool Cell::getStatus() const {
    return this->status;
}

sf::Vector2f Cell::getPosition() const {
    return this->shape.getPosition();
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (this->status) target.draw(this->shape, states);
}