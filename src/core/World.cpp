#include "core/World.hpp"
#include "config/TileHandler.hpp"

World::World() {}

void World::reset() {
    tileMap.clear();
}

void World::addTile(sf::Vector2f position, int type) {
    position = toGridPosition(position);
    Tile* tile = TileHandler::SwitchTile(position, type, this);
    std::cout << "\n Position x: \t" << position.x << "\n Position y: \t" << position.y << std::endl;
    tileMap[position] = tile;
}

std::vector<sf::Vector2f> World::getNeighbors(const sf::Vector2f& position) const {
    std::vector<sf::Vector2f> neighbors;
    neighbors.push_back(position + sf::Vector2f(-1, -1)); // Top-left
    neighbors.push_back(position + sf::Vector2f(0, -1));  // Top
    neighbors.push_back(position + sf::Vector2f(1, -1)); // Top-right
    neighbors.push_back(position + sf::Vector2f(-1, 0));  // Left
    neighbors.push_back(position + sf::Vector2f(1, 0));   // Right
    neighbors.push_back(position + sf::Vector2f(-1, 1)); // Bottom-left
    neighbors.push_back(position + sf::Vector2f(0, 1));   // Bottom
    neighbors.push_back(position + sf::Vector2f(1, 1));   // Bottom-right
    return neighbors;
}

Tile* World::getGridTile(const sf::Vector2f position) {
    auto it = tileMap.find(position);
    if (it != tileMap.end()) {
        return it->second;
    }
    return nullptr;
}

void World::update() {
    if (clock.getElapsedTime().asSeconds() >= Config::TIME_STEP) {
        std::vector<Tile*> tilesToUpdate;

        // Collect tiles to update
        for (auto& pair : tileMap) {
            tilesToUpdate.push_back(pair.second);
        }

        // Update from bottom to top
        std::sort(tilesToUpdate.begin(), tilesToUpdate.end(),
            [](Tile* a, Tile* b) { return a->position.y > b->position.y; });

        for (Tile* tile : tilesToUpdate) {
            sf::Vector2f oldPos = tile->position;
            tile->update();

            // Check collision with the ground
            if (tile->position.y >= Config::HEIGHT / Config::CELL_SIZE) {
                tile->setPos(oldPos);
                continue;
            }

            // Check collision with other tiles
            auto belowTile = getGridTile(tile->position);
            if (belowTile != nullptr && belowTile != tile) {
                tile->setPos(oldPos);
            } else if (tile->hasChanged) {
                tileMap.erase(oldPos);
                tileMap[tile->position] = tile;
                tile->hasChanged = false;
            }
        }

        clock.restart();
    }
}

void World::draw(sf::RenderWindow& window) {
    for (auto& pair : tileMap) {
        Tile* tile = pair.second;
        window.draw(tile->getShape());
    }
}

sf::Vector2f World::toGridPosition(sf::Vector2f position) {
    return sf::Vector2f(std::trunc(position.x / Config::CELL_SIZE), std::trunc(position.y / Config::CELL_SIZE));
}

bool World::VectorComparator::operator() (sf::Vector2f lhs, sf::Vector2f rhs) const {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}
