#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "core/Tile.hpp"
#include "config/Config.hpp"

struct VectorComparator
{
    bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
    {
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
};

class World {
public:
    std::map<sf::Vector2f, Tile*, VectorComparator> tileMap;
    sf::Clock clock;

    World();
    void reset();
    void addTile(sf::Vector2f position, int type);
    std::vector<sf::Vector2f> getNeighbors(const sf::Vector2f& position) const;
    Tile* getGridTile(const sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow& window);
    static sf::Vector2f toGridPosition(sf::Vector2f position);

private:
    struct VectorComparator {
        bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const;
    };
};

#endif // WORLD_H
