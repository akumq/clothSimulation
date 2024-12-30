#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include "core/World.hpp"
#include "config/TileHandler.hpp"

class InputHandler {
public:
    static bool mouse_pressed;

    static void handle_mouse_click(sf::Event event, sf::RenderWindow& window, World& world);
};

#endif // INPUT_HANDLER_H
