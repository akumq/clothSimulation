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
    window.setFramerateLimit(10);

    World world;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                init_simulation(world);
                InputHandler::handle_mouse_click(event,window,world);
        }
        


        window.clear(sf::Color(0, 0, 0, 0));
        sf::Vector2u windowSize = window.getSize();

        world.draw(window);
        world.update();

        window.display();
    }  

    // delete ptr_world;

    return 0;
} 