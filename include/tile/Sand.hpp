#ifndef SAND_H
#define SAND_H

#include "core/Tile.hpp"

class World;

class Sand : public Tile {
public:
    Sand(int x, int y, World* world);
    Sand(sf::Vector2f position, World* world);

    void update() override;
    sf::RectangleShape getShape() override;

private:
    World* world;

    bool checkCollision(const sf::Vector2f& pos);
};

#endif // SAND_H
