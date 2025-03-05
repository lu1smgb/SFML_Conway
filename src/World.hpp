#ifndef WORLD_HPP
#define WORLD_HPP

#include "Cell.hpp"

#include <vector>

typedef std::vector<Cell> CellRow_t;
typedef std::vector<CellRow_t> CellGrid_t;

class World : public sf::Drawable {
protected:
    CellGrid_t grid;
    sf::RectangleShape border;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    World(size_t width, size_t height, float cellScale);
    void setCellStatus(size_t row, size_t column, bool newStatus);
    inline bool getCellStatus(size_t row, size_t column);
    inline size_t getWidth() const;
    inline void setWidth(size_t width);
    inline size_t getHeight() const;
    inline void setHeight(size_t height);
    void setOffset(float x, float y);
    void setOffset(sf::Vector2f vec);

    void randomizeStatus(float alivePercentage);
};

#endif