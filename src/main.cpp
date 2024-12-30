#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/World.hpp"
#include "core/InputHandler.hpp"
#include "config/Config.hpp"

void init_simulation(World& world) {
    world.reset();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Config::WIDTH, Config::HEIGHT), "SFML Project");
    World world;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                init_simulation(world);
            InputHandler::handle_mouse_click(event, window, world);
        }

        window.clear(sf::Color(0, 0, 0, 0));
        world.draw(window);
        world.update();
        window.display();
    }

    return 0;
}
