#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "config/Config.hpp"

class Tile{

    public:
        sf::Vector2f position;
        bool hasChanged = false;

        Tile(int x,int y): position(x,y) {}; 

        Tile(sf::Vector2f position): position(position) {};

        void setPos(sf::Vector2f newPosition) {
            sf::Vector2f oldPosition = sf::Vector2f(position.x,position.y);
            position = sf::Vector2f(newPosition);
            if (oldPosition != newPosition){
                hasChanged = true;
            }

        }

        void setPos(float x, float y) {
            setPos(sf::Vector2f(x, y));
        }

        void setXPos(float x) {
            sf::Vector2f newPosition(x, position.y);
            setPos(newPosition);
        }

        void setYPos(float y) {
            sf::Vector2f newPosition(position.x, y);
            setPos(newPosition);
        }

        void update(){
            // std::cout << position.y << "/" << std::trunc(Config::HEIGHT / Config::CELL_SIZE) << std::endl;
            setYPos(std::min(position.y+1,std::trunc(Config::HEIGHT / Config::CELL_SIZE) -1));
        }

        sf::RectangleShape getShape(){
            sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
            rect.setPosition(position * Config::CELL_SIZE);
            rect.setFillColor(sf::Color::White);
            return rect;
        };

};

#endif // TILE_H