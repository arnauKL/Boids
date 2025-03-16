//
// Created by depre on 06/02/2025.
//

#include "Flock.h"

// Constructors and Destructors
Flock::Flock (const int flockSize)
{
    _flockSize = flockSize;
    _boids.reserve(_flockSize);
    for (int i = 0; i < _flockSize; i++)
    {
        const sf::Vector2f pos = sf::Vector2f(_random.rndFloat(0, conf::windowWidth), _random.rndFloat(0, conf::windowHeight));
        const sf::Vector2f vel = sf::Vector2f(_random.rndFloat(-conf::maxSpeed,conf::maxSpeed), _random.rndFloat(-conf::maxSpeed, conf::maxSpeed));
        _boids[i] = Boid(pos, vel, {0,0});
    }
    _triangleFlockVA = sf::VertexArray(sf::Triangles, _flockSize*3);
}

// Consulting functions
void Flock::updateTrianglesVA ()
{
    for (int i = 0; i < _flockSize; i++)
    {
        sf::Vector2f dir = VectorUtils::normalize(_boids[i]._velocity);
        sf::Vector2f perp(-dir.y, dir.x);

        const sf::Vector2f tip = _boids[i]._position + dir * conf::boidLength;
        const sf::Vector2f baseLeft = _boids[i]._position - dir * (conf::boidLength / 2.f) + perp * (conf::boidWidth / 2.f);
        const sf::Vector2f baseRight = _boids[i]._position - dir * (conf::boidLength / 2.f) - perp * (conf::boidWidth / 2.f);

        const int vertexOffset = i * 3;
        _triangleFlockVA[vertexOffset].position = tip;
        _triangleFlockVA[vertexOffset + 1].position = baseLeft;
        _triangleFlockVA[vertexOffset + 2].position = baseRight;

        _triangleFlockVA[vertexOffset].color = conf::boidColor;
        _triangleFlockVA[vertexOffset + 1].color = conf::boidColor;
        _triangleFlockVA[vertexOffset + 2].color = conf::boidColor;
    }
}

void Flock::draw (sf::RenderWindow& window) const
{
    /*
    for (int i = 0; i < _flockSize; i++)
    {
        sf::CircleShape shape;
        shape.setPosition(_boids[i]._position);
        shape.setRadius(conf::boidRadius);
        shape.setFillColor(sf::Color::White);
        window.draw(shape);
    }*/
    //window.draw(_flockVA);
    window.draw(_triangleFlockVA);
}

// Modifier functions
void Flock::update ()
{
    // Iterate over every boid
    for (int i = 0; i < _flockSize; i++)
    {
        // Calculate steering
        // ALIGNMENT
        sf::Vector2f avgDir = {0,0};
        sf::Vector2f alignmentSteering = {0,0};

        // COHESION
        sf::Vector2f avgPosition = {0,0};
        sf::Vector2f cohesionSteering = {0,0};

        // SEPARATION
        sf::Vector2f avgDist = {0,0};
        sf::Vector2f separationSteering = {0,0};

        int totalBoids = 0;

        // Check against all other boids
        for (int j = 0; j < _flockSize; j++)
        {
            // Avoid checking against itself
            if (i == j) continue;

            // Check if other boid is in range
            const float dist = VectorUtils::distance(_boids[i]._position, _boids[j]._position);

            if (dist < conf::perceptionRadius && dist > 0)
            {
                // Calculate average direction using the velocity
                avgDir = alignmentSteering + _boids[j]._velocity;

                // Calculate average position
                avgPosition = avgPosition + _boids[j]._position;

                // Find distance
                sf::Vector2f diff = _boids[i]._position - _boids[j]._position;
                diff /= (dist * dist);
                separationSteering += diff;

                totalBoids++;
            }
        }

        if (totalBoids > 0)
        {
            // Alignment
            avgDir.x /= totalBoids;
            avgDir.y /= totalBoids;
            // Set max speed
            alignmentSteering = avgDir - _boids[i]._velocity;
            alignmentSteering = VectorUtils::limit(alignmentSteering, conf::maxAlignmentForce);

            // Cohesion
            avgPosition.x /= totalBoids;
            avgPosition.y /= totalBoids;
            cohesionSteering = avgPosition - _boids[i]._position;
            cohesionSteering = cohesionSteering - _boids[i]._velocity;
            cohesionSteering = VectorUtils::limit(cohesionSteering, conf::maxCohesionForce);

            // Separation
            separationSteering = VectorUtils::limit(separationSteering, conf::maxSeparationForce);
        }

        _boids[i]._acceleration = cohesionSteering + alignmentSteering + separationSteering;
        _boids[i].update();
    }
}