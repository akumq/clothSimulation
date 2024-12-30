#ifndef SAND_H
#define SAND_H

#include "core/Tile.hpp"
#include "core/World.hpp"

class Sand : public Tile {
public:
    Sand(int x, int y, World* world) : Tile(x, y), world(world) {}
    Sand(sf::Vector2f position, World* world) : Tile(position), world(world) {}

    void update() override {
        if (!pinned) {
            sf::Vector2f newPosition = position;
            
            // Check bottom
            newPosition.y += 1;
            if (!checkCollision(newPosition)) {
                setPos(newPosition);
                return;
            }

            // Check bottom-left
            newPosition = position + sf::Vector2f(-1, 1);
            if (!checkCollision(newPosition)) {
                setPos(newPosition);
                return;
            }

            // Check bottom-right
            newPosition = position + sf::Vector2f(1, 1);
            if (!checkCollision(newPosition)) {
                setPos(newPosition);
                return;
            }
        }
    }

    sf::RectangleShape getShape() override {
        sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
        rect.setPosition(position * Config::CELL_SIZE);
        rect.setFillColor(sf::Color(194, 178, 128));
        return rect;
    }

private:
    World* world;

    bool checkCollision(const sf::Vector2f& pos) {
        // Check world bounds
        if (pos.x < 0 || pos.x >= Config::WIDTH / Config::CELL_SIZE ||
            pos.y < 0 || pos.y >= Config::HEIGHT / Config::CELL_SIZE) {
            return true;
        }

        // Check other particles
        return world->getGridTile(pos) != nullptr;
    }
};

#endif // SAND_H