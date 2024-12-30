#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SFML/Graphics.hpp>
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
        std::map<sf::Vector2f, Tile*,VectorComparator> tileMap;

        World(){
        }
        void reset(){
            std::map<sf::Vector2f, Tile*,VectorComparator> tileMap;
        }

        void addTile(sf::Vector2f position){
            position = toGridPosition(position);
            std::cout << "\n Position x: \t" << position.x << "\n Position y: \t" << position.y << std::endl;
            tileMap[position] = new Tile(position);
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
        
        void update(){
            for (auto it = tileMap.begin(); it != tileMap.end();) {
                Tile* tile = it->second;
                if (tile->hasChanged) {
                    sf::Vector2f oldPosition = it->first;
                    sf::Vector2f newPosition = tile->position;
                    tileMap[newPosition] = tile;
                    std::swap(tileMap[newPosition], it->second);
                    it = tileMap.erase(it);
                    tile->hasChanged = false;
                } else {
                    ++it;
                }
                tile->update();
            }
        }

        // void moveTile(sf::Vector2f oldPosition, sf::Vector2f newPosition) {
        //     std::cout << "\n old: \t"<< oldPosition.y << "\n new: \t"<<newPosition.y << std::endl;
        //     auto it = tileMap.find(oldPosition);
        //     // Tile tile = *it->second;
        //     // tileMap.erase(oldPosition);
        //     // tileMap[newPosition] = &tile;
        //     if (it != tileMap.end()) {
        //         Tile* tile = it->second;
        //         tileMap.erase(it);
        //         tileMap[newPosition] = tile;
        //     } else {
        //         std::cout << "No tile found at position (" << oldPosition.x << ", " << oldPosition.y << ")" << std::endl;
        //     }
        // }

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