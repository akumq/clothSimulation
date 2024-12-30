#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "config/Config.hpp"

class Tile {
public:
    sf::Vector2f position;
    sf::Vector2f previous_position;
    sf::Vector2f acceleration;
    bool pinned;
    bool hasChanged = false;

    Tile(int x, int y);
    Tile(sf::Vector2f position);

    void setPos(sf::Vector2f newPosition);
    void setPos(float x, float y);

    virtual void update();
    virtual sf::RectangleShape getShape();
};

#endif // TILE_H
