#pragma once
#include "SFML/Graphics.hpp"

namespace conf {
    constexpr int windowWidth = 1920;
    constexpr int windowHeight = 1280;

    //inline sf::Color bgColor = sf::Color::Black;
    //inline sf::Color boidColor = sf::Color::White;

    inline sf::Color bgColor = sf::Color(135, 206, 235);
    inline sf::Color boidColor = sf::Color(15, 15, 18);

    constexpr int nBoids = 2000;
    //constexpr int boidRadius = 2;

    constexpr float perceptionRadius = 15.0f;

    inline float maxAlignmentForce = 1.0f;
    inline float maxCohesionForce = 0.2;
    inline float maxSeparationForce = 0.1;

    constexpr float boidLength = 5.0f;
    constexpr float boidWidth = 3.0f;


    constexpr float maxSpeed = 4.0f;
};