#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Resources.hpp"
#include "ClockSystem.hpp"

class App {
private:
    static void start();

    static void update();

    static void draw();

    static void shutdown();

public:
    static sf::RenderWindow window;
    static Resources resources;
    static ClockSystem clock;

    static void run();
};
