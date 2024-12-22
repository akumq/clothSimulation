#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "object/Particle.h"
#include "core/Constraint.h"

const float CLICK_TOLERANCE = 10.0f;

class InputHandler {
    public:
        static float cut_radius;  // Rayon de coupe modifiable

        static void handle_mouse_click(const sf::Event& event, const sf::RenderWindow& window,
                                     std::vector<Particle>& particles, std::vector<Constraint>& constraints){
            // Gérer le rayon avec les flèches
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        cut_radius += 2.0f;
                        cut_radius = std::min(cut_radius, 50.0f);
                        break;
                    case sf::Keyboard::Down:
                        cut_radius -= 2.0f;
                        cut_radius = std::max(cut_radius, 5.0f);
                        break;
                }
            }

            // Gérer le clic
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                mouse_pressed = true;
            }
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                mouse_pressed = false;
            }

            if(mouse_pressed){
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                tear_cloth(mouse_pos.x, mouse_pos.y, particles, constraints);
            }
        }

        static void draw_cut_radius(sf::RenderWindow& window) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            sf::CircleShape circle(cut_radius);
            circle.setPosition(mouse_pos.x - cut_radius, mouse_pos.y - cut_radius);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::Red);
            circle.setOutlineThickness(1.0f);
            window.draw(circle);
        }

    private:
        static bool mouse_pressed;

        static float point_to_segment_distance(float px, float py, float x1, float y1, float x2, float y2) {
            float ABx = x2 - x1;
            float ABy = y2 - y1;

            float APx = px - x1;
            float APy = py - y1;

            float BPx = px - x2;
            float BPy = py - y2;

            float AB_AP = ABx * APx + ABy * APy;
            float AB_AB = ABx * ABx + ABy * ABy;
            float t = AB_AP / AB_AB;

            if (t < 0.0f) {
                return std::sqrt(APx * APx + APy * APy);
            }
            else if (t > 1.0f) {
                return std::sqrt(BPx * BPx + BPy * BPy);
            }
            else {
                float proj_x = x1 + t * ABx;
                float proj_y = y1 + t * ABy;
                return std::sqrt((px - proj_x) * (px - proj_x) + (py - proj_y) * (py - proj_y));
            }
        }

         static Constraint* find_nearest_constraint(float mouse_x, float mouse_y,
                                    const std::vector<Constraint>& constraints) {
                Constraint *nearest_constraint = nullptr;
                float min_distance = CLICK_TOLERANCE;

                for (const auto& constraint : constraints) {
                    float distatnce = point_to_segment_distance(mouse_x, mouse_y,
                                        constraint.p1->position.x, constraint.p1->position.y,
                                        constraint.p2->position.x, constraint.p2->position.y);
                    if (distatnce < min_distance) {
                        min_distance = distatnce;
                        nearest_constraint = const_cast<Constraint*>(&constraint);
                    }
                }
            return nearest_constraint;
        }
        
        static void tear_cloth(float mouse_x, float mouse_y, std::vector<Particle>& particles,
                                std::vector<Constraint>& constraints) {
            for(auto& constraint : constraints) {
                if(constraint.active) {
                    float distance = point_to_segment_distance(mouse_x, mouse_y,
                                    constraint.p1->position.x, constraint.p1->position.y,
                                    constraint.p2->position.x, constraint.p2->position.y);
                    if(distance < cut_radius) {
                        constraint.deactivate();
                    }
                }
            }
        }
};

bool InputHandler::mouse_pressed = false;
float InputHandler::cut_radius = 10.0f;

#endif // INPUT_HANDLER_H