#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable {
protected:
    sf::RectangleShape shape;
    bool status;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Cell();
    Cell(sf::Vector2f position, bool status, unsigned short int scale, sf::Color color);
    void setPosition(sf::Vector2f position);
    void setScale(unsigned short int scale);
    void setColor(sf::Color color);
    void setStatus(bool status);
    bool getStatus() const;
    sf::Vector2f getPosition() const;
};

#endif