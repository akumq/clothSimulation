#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include "core/World.hpp"
#include "core/Tile.hpp"

#include "config/TileHandler.hpp"


class InputHandler{

    public:
        static bool mouse_pressed;

        static void handle_mouse_click(sf::Event event, sf::RenderWindow& window, World& world){
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                mouse_pressed = true;
            }
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                mouse_pressed = false;
            }

            if(mouse_pressed){
                sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);
                world.addTile(mouse_pos,TileHandler::SAND);
            }
        };

};

bool InputHandler::mouse_pressed = false;

#endif // INPUT_HANDLER_H

