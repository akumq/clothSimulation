#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/Tile.hpp"

#include "config/Config.hpp"
#include "config/TileHandler.hpp"



struct VectorComparator
{
    bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const
    {
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
};

class World {

    public:
        std::map<sf::Vector2f, Tile*,VectorComparator> tileMap;
        sf::Clock clock;

        World(){
        }
        void reset(){
            std::map<sf::Vector2f, Tile*,VectorComparator> tileMap;
        }

        void addTile(sf::Vector2f position, int type){
            position = toGridPosition(position);
            Tile* tile = TileHandler::SwitchTile(position, type, this);
            std::cout << "\n Position x: \t" << position.x << "\n Position y: \t" << position.y << std::endl;
            tileMap[position] = tile;
        }

        std::vector<sf::Vector2f> getNeighbors(const sf::Vector2f& position) const {
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

        Tile* getGridTile(const sf::Vector2f position) {
            auto it = tileMap.find(position);
            if (it != tileMap.end()) {
                return it->second;
            }
            return nullptr;
        }
        
        void update() {
            if (clock.getElapsedTime().asSeconds() >= Config::TIME_STEP) {
                std::vector<Tile*> tilesToUpdate;
                
                // Collecter les tuiles à mettre à jour
                for (auto& pair : tileMap) {
                    tilesToUpdate.push_back(pair.second);
                }
                
                // Mettre à jour du bas vers le haut
                std::sort(tilesToUpdate.begin(), tilesToUpdate.end(), 
                    [](Tile* a, Tile* b) { return a->position.y > b->position.y; });
                
                for (Tile* tile : tilesToUpdate) {
                    sf::Vector2f oldPos = tile->position;
                    tile->update();
                    
                    // Vérifier collision avec le sol
                    if (tile->position.y >= Config::HEIGHT / Config::CELL_SIZE) {
                        tile->setPos(oldPos);
                        continue;
                    }
                    
                    // Vérifier collision avec autre tuile
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

        void draw(sf::RenderWindow& window){
           for (auto& pair : tileMap) {
                Tile* tile = pair.second;
                // std::cout << tile->position.x << std::endl;
                window.draw(tile->getShape());
            }
        }

        static sf::Vector2f toGridPosition(sf::Vector2f position){
            return sf::Vector2f(std::trunc(position.x / Config::CELL_SIZE), std::trunc(position.y / Config::CELL_SIZE));
        }

        
};

#endif // WORLD_H