#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "config/Config.hpp"

class Tile{
    public:
        sf::Vector2f position;
        sf::Vector2f previous_position;
        sf::Vector2f acceleration;
        bool pinned;    
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


        virtual void update() {
            if (!pinned) {
                sf::Vector2f newPosition = position;
                newPosition.y += 1; // Déplacement d'une case à la fois
                
                setPos(newPosition);
            }
        }

        virtual sf::RectangleShape getShape(){
            sf::RectangleShape rect(sf::Vector2f(Config::CELL_SIZE, Config::CELL_SIZE));
            rect.setPosition(position * Config::CELL_SIZE);
            rect.setFillColor(sf::Color::White);
            return rect;
        };


};

#endif // TILE_H