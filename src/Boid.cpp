//
// Created by depre on 06/02/2025.
//

#include "Boid.h"

Boid::Boid ()
{
    _position = {0,0};
    _velocity = {0,0};
    _acceleration = {0,0};
}

Boid::Boid(const sf::Vector2f pos)
{
    _position = pos;
    _velocity = {0,0};
    _acceleration = {0,0};
}

Boid::Boid (const sf::Vector2f pos, const sf::Vector2f vel, const sf::Vector2f acc)
{
    _position = pos;
    _velocity = vel;
    _acceleration = acc;
}

void Boid::update ()
{
    _velocity += _acceleration;
    _velocity = VectorUtils::setMagnitude(_velocity, conf::maxSpeed);
    _position += _velocity;

    if (_position.x < 0) _position.x = conf::windowWidth;
    else if (_position.x > conf::windowWidth) _position.x = 0;
    if (_position.y < 0) _position.y = conf::windowHeight;
    else if (_position.y > conf::windowHeight) _position.y = 0;
}
