#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
    public:
        sf::Vector2f position;
        sf::Vector2f previous_position;
        sf::Vector2f acceleration;
        bool pinned;    

        Particle(float x, float y, bool pinned) : position(x,y), previous_position(x,y), acceleration(0.0f, 0.0f), pinned(pinned){}

        void apply_force(const sf::Vector2f& force) {
            if(!pinned) {   
                acceleration += force;
            }
        }

        void update(float time_step) {
            // verlet integration  
            if(!pinned) {
                sf::Vector2f velocity = position - previous_position;
                sf::Vector2f temp_position = position; // Sauvegarder la position actuelle
                position += velocity + acceleration * time_step * time_step;
                previous_position = temp_position;
                acceleration = sf::Vector2f(0, 0); 
            }
        }
        
        void constrain_to_bounds(int width, int height) {
            sf::Vector2f velocity = position - previous_position;
            const float restitution = 0.6f;
            
            if(position.x < 0) {
                position.x = 0;
                previous_position.x = position.x + velocity.x * restitution;
            } 
            if(position.x > width) {
                position.x = width;
                previous_position.x = position.x + velocity.x * restitution;
            }
            if(position.y < 0) {
                position.y = 0;
                previous_position.y = position.y + velocity.y * restitution;
            }   
            if(position.y > height) {
                position.y = height;
                previous_position.y = position.y + velocity.y * restitution;
            }   
        }
};

#endif //PARTICLE_H
