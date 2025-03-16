//
// Created by depre on 06/02/2025.
//

#ifndef BOID_H
#define BOID_H

#include "conf.hpp"
#include "utils/VectorUtils.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>

class Boid {
public:
    Boid();
    explicit Boid(sf::Vector2f pos);
    Boid(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc);

    void update();

    sf::Vector2f _position;
    sf::Vector2f _velocity;
    sf::Vector2f _acceleration;
};



#endif //BOID_H
