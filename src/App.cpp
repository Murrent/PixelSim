#include <SFML/Window/Event.hpp>
#include "App.hpp"

sf::RenderWindow App::window;
Resources App::resources;
ClockSystem App::clock;

void App::start() {
    window.create(sf::VideoMode(800, 600), "Pixels");
}

void App::update() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void App::draw() {
    window.display();
}

void App::shutdown() {

}

void App::run() {
    start();
    while (window.isOpen()) {
        update();
        draw();
    }
    shutdown();
}
