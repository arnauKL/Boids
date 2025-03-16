#ifndef VECTOR_UTILS_HPP
#define VECTOR_UTILS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

namespace VectorUtils {

    inline float distance(const sf::Vector2f &v1, const sf::Vector2f &v2) {
        return std::sqrt((v2.x - v1.x)*(v2.x - v1.x) + (v2.x - v1.x)*(v2.y - v1.y));
    }

    inline float magnitude(const sf::Vector2f& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    inline sf::Vector2f setMagnitude(const sf::Vector2f& v, const float newMagnitude) {
        const float currentMag = magnitude(v);
        if (currentMag == 0)
            return v;
        return {v.x / currentMag * newMagnitude, v.y / currentMag * newMagnitude};
    }

    inline sf::Vector2f limit(const sf::Vector2f& v, const float limit) {
        const float currentMag = magnitude(v);
        if (currentMag >= limit)
            return {v.x / currentMag * limit, v.y / currentMag * limit};
        return v;
    }

    inline float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
        return a.x * b.x + a.y * b.y;
    }

    inline sf::Vector2f normalize(const sf::Vector2f& v) {
        float mag = magnitude(v);
        if (mag == 0) return {0, 0};
        return {v.x / mag, v.y / mag};
    }

    inline sf::Vector2f divide(const sf::Vector2f& v, const float divisor)
    {
        return {v.x / divisor, v.y / divisor};
    }
}

#endif // VECTOR_UTILS_HPP
