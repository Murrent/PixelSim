#include "ClockSystem.hpp"

void ClockSystem::update() {
    float timeNow = clock.getElapsedTime().asSeconds();
    deltaTime = timeNow - lastUpdate;
    lastUpdate = timeNow;
}

void ClockSystem::restart() {
    clock.restart();
}

float ClockSystem::getElapsedSec() const {
    return clock.getElapsedTime().asSeconds();
}

sf::Int32 ClockSystem::getElapsedMil() const {
    return clock.getElapsedTime().asMilliseconds();
}

sf::Int64 ClockSystem::getElapsedMic() const {
    return clock.getElapsedTime().asMicroseconds();
}

float ClockSystem::delta() const {
    return deltaTime;
}
