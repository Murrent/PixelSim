#pragma once


#include <SFML/System/Clock.hpp>

class ClockSystem {
private:
    sf::Clock clock;
    float deltaTime{}, lastUpdate{};

public:
    void update();

    void restart();

    float getElapsedSec() const;

    sf::Int32 getElapsedMil() const;

    sf::Int64 getElapsedMic() const;

    float delta() const;
};

