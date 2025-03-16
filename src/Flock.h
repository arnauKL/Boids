//
// Created by depre on 06/02/2025.
//

#ifndef FLOCK_H
#define FLOCK_H
#include "Boid.h"
#include "conf.hpp"
#include "utils/Random.h"
#include "utils/VectorUtils.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Flock {

public:
    explicit Flock (int flockSize);

    void draw(sf::RenderWindow &window) const;
    void updateTrianglesVA ();

    void update();

private:
    std::vector<Boid> _boids;
    int _flockSize;
    sf::VertexArray _flockVA;
    sf::VertexArray _triangleFlockVA;
    Random _random;
};



#endif //FLOCK_H
