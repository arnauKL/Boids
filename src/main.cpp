#include "conf.hpp"
#include "Flock.h"
#include <SFML/Graphics.hpp>


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(conf::windowWidth, conf::windowHeight), "Boids", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Flock flock = Flock(conf::nBoids);

    sf::VertexArray gradient(sf::Quads, 4);

    sf::Color topColor(135, 206, 235); // Light Sky Blue
    sf::Color bottomColor(244, 230, 70); // Deep Sky Blue

    gradient[0].position = sf::Vector2f(0, 0);
    gradient[1].position = sf::Vector2f(conf::windowWidth, 0);
    gradient[2].position = sf::Vector2f(conf::windowWidth, conf::windowHeight);
    gradient[3].position = sf::Vector2f(0, conf::windowHeight);

    gradient[0].color = bottomColor;
    gradient[1].color = topColor;
    gradient[2].color = topColor;
    gradient[3].color = topColor;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                // Alignment force
                if (event.key.code == sf::Keyboard::Q) conf::maxAlignmentForce += 0.05;
                if (event.key.code == sf::Keyboard::A) conf::maxAlignmentForce -= 0.05;

                // Separation force
                if (event.key.code == sf::Keyboard::W) conf::maxSeparationForce += 0.05;
                if (event.key.code == sf::Keyboard::S) conf::maxSeparationForce -= 0.05;

                // Cohesion force
                if (event.key.code == sf::Keyboard::E) conf::maxCohesionForce += 0.05;
                if (event.key.code == sf::Keyboard::D) conf::maxCohesionForce -= 0.05;


                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
        // UPDATE
        flock.update();

        // RENDER
        //flock.updateVA();
        flock.updateTrianglesVA();
        flock.draw(window);
        window.display();


        window.clear(conf::bgColor);
        window.draw(gradient);
    }
}