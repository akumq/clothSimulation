#include <SFML/Graphics.hpp>
#include <iostream>

#include "object/Particle.h"
#include "core/Constraint.h"
#include "core/InputHandler.h"

const int WIDTH = 1080;
const int HEIGHT = 640;

const float GRAVITY = 10.0f;
const float TIME_STEP = 0.1f;

const int ROW = 100;
const int COL = 100;
const float REST_DISTANCE = 2.0f;

void init_simulation(std::vector<Particle>& particles, std::vector<Constraint>& constraints) {
    particles.clear();
    constraints.clear();
    
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            float x = col * REST_DISTANCE + WIDTH/3;
            float y = row * REST_DISTANCE + HEIGHT/3;
            bool pinned = (row == 0);
            particles.emplace_back(x, y, pinned);
        }
    }
    
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (col < COL - 1) {
                constraints.emplace_back(&particles[row * COL + col], 
                                      &particles[row * COL + col + 1]);
            }
            if (row < ROW - 1) {
                constraints.emplace_back(&particles[row * COL + col], 
                                      &particles[(row + 1) * COL + col]);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Project");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    init_simulation(particles, constraints);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                init_simulation(particles, constraints);

            InputHandler::handle_mouse_click(event, window, particles, constraints);
        }
        
        window.clear(sf::Color(0, 0, 0, 0));

        for (auto& particle : particles) {
            particle.apply_force(sf::Vector2f(0.0f, GRAVITY));
            particle.update(TIME_STEP);
            particle.constrain_to_bounds(WIDTH, HEIGHT);
        }

        for(size_t i = 0; i < 5; i++) {
            for(auto& constraint : constraints) {
                constraint.satisfy();
            }
        }   

        for (const auto& particle : particles) {
            sf::Vertex point(particle.position, sf::Color::White);
            window.draw(&point, 1, sf::Points);
        }

        for(const auto& constraint : constraints) {
            if(constraint.active) {
                sf::Vertex line[] = {
                    sf::Vertex(constraint.p1->position, sf::Color::White),
                    sf::Vertex(constraint.p2->position, sf::Color::White),
                };
                window.draw(line, 2, sf::Lines);
            }
        }

        // Dessiner le rayon de coupe
        InputHandler::draw_cut_radius(window);

        window.display();
    }

    return 0;
} 