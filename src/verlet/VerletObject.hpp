#pragma once


#include <SFML/System/Vector2.hpp>
#include <cmath>

class VerletObject {
public:
    sf::Vector2f position;
    sf::Vector2f prevPosition;
    sf::Vector2f acceleration;
    float size{10.0f};
    bool staticBody{false};

    void updatePos(float dt) {
        if (staticBody) return;
        const sf::Vector2f velocity = (position - prevPosition);// * std::pow(0.5f, dt);

        prevPosition = position;

        position = position + velocity + acceleration * dt * dt;

        acceleration = {0, 0};
    }

    void accelerate(sf::Vector2f acc) {
        acceleration += acc;
    }
};

