#include <SFML/Graphics.hpp>
#include <iostream>
#include "Solver.hpp"
#include "Link.hpp"
#include <cstdlib>


std::vector<VerletObject> objects;
std::vector<Link> links;
std::vector<sf::Color> colors;
sf::CircleShape shape;
sf::RectangleShape rect;
sf::Text text;

//void createMenu(sf::RenderWindow &window) {
//    const float connectRadiusMultiplier = 2.0f;
//    bool leftPressLock = false;
//    uint32_t selectedObj = -1;
//    float tmpRadius = 10.0f;
//    sf::Vector2f tmpPos;
//    std::vector<uint32_t> inConnectRadius;
//
//    while (window.isOpen()) {
//
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            else if (event.type == sf::Event::MouseWheelScrolled) {
//                tmpRadius += event.mouseWheelScroll.delta;
//                if (tmpRadius < 5.0f)
//                    tmpRadius = 5.0f;
//            }
//        }
//
//        sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window) - window.getView().getSize() * 0.5f;
//
//        mousePos.x = (int) std::floor(mousePos.x / (tmpRadius + tmpRadius)) * (int) (tmpRadius + tmpRadius);
//        mousePos.y = (int) std::floor(mousePos.y / (tmpRadius + tmpRadius)) * (int) (tmpRadius + tmpRadius);
//
//        if (!objects.empty()) {
//            sf::Vector2f closestCircle = {};
//            float closestDistance = -1;
//            for (int i = 0; i < objects.size(); i++) {
//                VerletObject &object = objects[i];
//                float dist = Dist(mousePos, object.position) - tmpRadius - Solver::particleSize;
//                Vector2f normal = Normal(mousePos, object.position);
//                int posX = (int) std::floor(mousePos.x / (tmpRadius + tmpRadius)) * (int) (tmpRadius + tmpRadius);
//                int posY = (int) std::floor(mousePos.y / (tmpRadius + tmpRadius)) * (int) (tmpRadius + tmpRadius);
//                Vector2f finalPos = sf::Vector2f(posX, posY);//object.position + normal * (object.size + tmpRadius);
//                bool collision = false;
//                for (auto &otherObj: objects) {
//                    if (&otherObj == &object) continue;
//                    if (Dist(finalPos, otherObj.position) < tmpRadius + Solver::particleSize) {
//                        collision = true;
//                        break;
//                    }
//                }
//                if (!collision && (closestDistance == -1 || dist < closestDistance)) {
//                    closestDistance = dist;
//                    closestCircle = finalPos;
//
//                }
//            }
//            if (closestDistance != -1) {
//                tmpPos = closestCircle;
//                for (int k = 0; k < objects.size(); k++) {
//                    //if (k == i) continue;
//                    VerletObject &otherObj = objects[k];
//                    if (Dist(closestCircle, otherObj.position) <
//                        (tmpRadius + Solver::particleSize) * connectRadiusMultiplier)
//                        inConnectRadius.emplace_back(k);
//                }
//            }
//        } else {
//            tmpPos = mousePos;
//        }
//
//
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftPressLock) {
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
//                if (selectedObj == -1) {
//                    for (int i = 0; i < objects.size(); i++) {
//                        if (Dist(mousePos, objects[i].position) < Solver::particleSize)
//                            selectedObj = i;
//                    }
//                } else {
//                    for (int i = 0; i < objects.size(); i++) {
//                        if (i == selectedObj) continue;
//                        if (Dist(mousePos, objects[i].position) < Solver::particleSize) {
//                            links.emplace_back();
//                            Link &link = links[links.size() - 1];
//                            link.object1 = selectedObj;
//                            link.object2 = i;
//                            link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//                            //link.direction = objects[link.object2].position - objects[link.object1].position;
//                            selectedObj = -1;
//                        }
//                    }
//                }
//            } else {
//                objects.emplace_back();
//                VerletObject &obj = objects[objects.size() - 1];
//                obj.position = tmpPos;
//                obj.prevPosition = tmpPos;
//                colors.emplace_back();
//                colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//                for (auto &i: inConnectRadius) {
//                    links.emplace_back();
//                    Link &link = links[links.size() - 1];
//                    link.object1 = objects.size() - 1;
//                    link.object2 = i;
//                    link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//                    //link.direction = objects[link.object2].position - objects[link.object1].position;
//                }
////                for (int i = 0; i < objects.size(); ++i) {
////                    for (int j = i + 1; j < objects.size(); ++j) {
////                        links.emplace_back();
////                        Link &link = links[links.size() - 1];
////                        link.object1 = i;
////                        link.object2 = j;
////                        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
////                    }
////                }
//            }
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//            return;
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//            leftPressLock = true;
//        } else {
//            leftPressLock = false;
//        }
//
//        window.clear(sf::Color(150, 150, 150));
//
//        for (int i = 0; i < objects.size(); i++) {
//            shape.setRadius(Solver::particleSize);
//            shape.setOrigin(Solver::particleSize, Solver::particleSize);
//            shape.setPosition(objects[i].position);
//            if (selectedObj == i)
//                shape.setFillColor(sf::Color::Green);
//            else
//                shape.setFillColor(colors[i]);
//            window.draw(shape);
//        }
//        shape.setFillColor(sf::Color::Red);
//        shape.setRadius(tmpRadius);
//        shape.setOrigin(tmpRadius, tmpRadius);
//        shape.setPosition(tmpPos);
//        window.draw(shape);
//
//        for (auto &con: inConnectRadius) {
//            std::cout << inConnectRadius.size() << std::endl;
//            sf::VertexArray lines(sf::LinesStrip, 2);
//            lines[0].position = objects[con].position;
//            lines[0].color = sf::Color::Red;
//            lines[1].position = tmpPos;
//            lines[1].color = sf::Color::Red;
//
//            window.draw(lines);
//        }
//
//        inConnectRadius.clear();
//        window.display();
//    }
//}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080) * 0.02f);
    window.setView(view);
    window.setFramerateLimit(60);

    text.setFillColor(sf::Color::Black);
    sf::Font font;
    if (!font.loadFromFile("../assets/TAHOMA_0.TTF"))
        return 0;
    text.setFont(font);

    for (int i = 0; i < 2; ++i) {
        objects.emplace_back();
        VerletObject &obj = objects[objects.size() - 1];
        obj.position = sf::Vector2f(3 + i * 2, 3);
        obj.prevPosition = sf::Vector2f(3.001f + i * 2, 3);
        obj.staticBody = false;
        colors.emplace_back();
        colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
    }

    //createMenu(window);
//    for (int i = 0; i < objects.size(); ++i) {
//        for (int j = i + 1; j < objects.size(); ++j) {
//            links.emplace_back();
//            Link &link = links[links.size() - 1];
//            link.object1 = i;
//            link.object2 = j;
//            link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//        }
//    }

    //std::cout << "links: " << links.size() << std::endl;
    Solver solver;
    solver.start();

//    const int chainLength = 20;
//    for (int i = 0; i < chainLength; ++i) {
//        objects.emplace_back();
//        objects[i].position = sf::Vector2f(-200.0f + (float) i * 20.0f, 0);
//        objects[i].prevPosition = sf::Vector2f(-200.0f + (float) i * 20.0f, 0);
//        colors.emplace_back();
//        colors[objects.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//    }


//    colors.emplace_back();
//    colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//    colors.emplace_back();
//    colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//    colors.emplace_back();
//    colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//    colors.emplace_back();
//    colors[colors.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//
//    objects.emplace_back();
//    objects.emplace_back();
//    objects.emplace_back();
//    objects.emplace_back();
//    objects[0].position = sf::Vector2f(0, 0);
//    objects[0].prevPosition = sf::Vector2f(0, 0);
//    objects[1].position = sf::Vector2f(20, 0);
//    objects[1].prevPosition = sf::Vector2f(20, 0);
//    objects[2].position = sf::Vector2f(0, 20);
//    objects[2].prevPosition = sf::Vector2f(0, 20);
//    objects[3].position = sf::Vector2f(20, 20);
//    objects[3].prevPosition = sf::Vector2f(20, 20);
//    objects[0].staticBody = true;
//    objects[1].staticBody = true;
//    // 0
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 0;
//        link.object2 = 1;
//        link.targetDistance = objects[link.object1].size + objects[link.object2].size;
//    }
//    // 1
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 1;
//        link.object2 = 3;
//        link.targetDistance = objects[link.object1].size + objects[link.object2].size;
//    }
//    // 2
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 2;
//        link.object2 = 3;
//        link.targetDistance = objects[link.object1].size + objects[link.object2].size;
//    }
//    // 3
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 0;
//        link.object2 = 2;
//        link.targetDistance = objects[link.object1].size + objects[link.object2].size;
//    }
//
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 0;
//        link.object2 = 3;
//        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//    }
//    {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = 1;
//        link.object2 = 2;
//        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//    }

    //objects[0].staticBody = true;
//    objects[chainLength - 1].staticBody = true;
//    for (int i = 0; i < chainLength - 1; ++i) {
//        links.emplace_back();
//        Link &link = links[links.size() - 1];
//        link.object1 = i;
//        link.object2 = i + 1;
//        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//    }


    srand(time(NULL));

    sf::Clock clock;
    sf::Clock fpsClock;
    sf::Clock eventClock;
    float delta = 0;
//    while (delta < 1) {
//        delta = clock.getElapsedTime().asSeconds();
//        window.clear(sf::Color(150, 150, 150));
//
//        rect.setFillColor(sf::Color::Cyan);
//        rect.setSize(sf::Vector2f(Solver::gridX * Solver::particleSize, Solver::gridY * Solver::particleSize));
//        rect.setPosition(sf::Vector2f(0, 0));
//        window.draw(rect);
//
//        for (auto &obj: objects) {
//            shape.setFillColor(sf::Color::Red);
//            shape.setRadius(Solver::particleSize);
//            shape.setOrigin(Solver::particleSize, Solver::particleSize);
//            shape.setPosition(obj.position);
//            window.draw(shape);
//        }
//
//
//        window.display();
//    }

    clock.restart();
    std::cout << "Starting loop" << std::endl;
    while (window.isOpen()) {
        float frameTime = fpsClock.getElapsedTime().asSeconds();
        fpsClock.restart();
        float fps = 1.0f / frameTime;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window) - window.getView().getSize() * 0.5f;

//        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && eventClock.getElapsedTime().asSeconds() > 0.2f) {
//            objects.emplace_back();
//            colors.emplace_back();
//            objects[objects.size() - 1].position.x = 0;
//            objects[objects.size() - 1].prevPosition.x = 0;
//            objects[objects.size() - 1].position.y = -200;
//            objects[objects.size() - 1].prevPosition.y = -200;
//            objects[objects.size() - 1].accelerate(sf::Vector2f(1, 0));
//            colors[objects.size() - 1] = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//
//            eventClock.restart();
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && eventClock.getElapsedTime().asSeconds() > 0.5f) {
//            sf::Color color = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//            int size = 5;
//            for (int j = 0; j < 5; ++j) {
//                for (int i = 0; i < 5; ++i) {
//                    objects.emplace_back();
//                    colors.emplace_back();
//                    objects[objects.size() - 1].position.x = mousePos.x + i * size * 2;
//                    objects[objects.size() - 1].prevPosition.x = mousePos.x + i * size * 2;
//                    objects[objects.size() - 1].position.y = mousePos.y + j * size * 2;
//                    objects[objects.size() - 1].prevPosition.y = mousePos.y + j * size * 2;
//                    objects[objects.size() - 1].accelerate(sf::Vector2f(0, 0));
//                    colors[objects.size() - 1] = color;
//                    bool setX = false, setY = false;
//                    if (i != 0) {
//                        links.emplace_back();
//                        Link &link = links[links.size() - 1];
//                        link.object1 = objects.size() - 1;
//                        link.object2 = objects.size() - 2;
//                        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//                        setX = true;
//                    }
//                    if (j != 0) {
//                        links.emplace_back();
//                        Link &link = links[links.size() - 1];
//                        link.object1 = objects.size() - 1;
//                        link.object2 = objects.size() - 6;
//                        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//                        setY = true;
//                    }
//                    if (setX && setY) {
//                        links.emplace_back();
//                        Link &link = links[links.size() - 1];
//                        link.object1 = objects.size() - 1;
//                        link.object2 = objects.size() - 7;
//                        link.targetDistance = Dist(objects[link.object1].position, objects[link.object2].position);
//                    }
//                }
//            }
//
//            eventClock.restart();
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && eventClock.getElapsedTime().asSeconds() > 0.5f) {
//            sf::Color color = sf::Color(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0);
//            int size = 5;
//            for (int j = 0; j < 20; ++j) {
//                for (int i = 0; i < 20; ++i) {
//                    objects.emplace_back();
//                    colors.emplace_back();
//                    objects[objects.size() - 1].position.x = mousePos.x + i * size * 2;
//                    objects[objects.size() - 1].prevPosition.x = mousePos.x + i * size * 2;
//                    objects[objects.size() - 1].position.y = mousePos.y + j * size * 2;
//                    objects[objects.size() - 1].prevPosition.y = mousePos.y + j * size * 2;
//                    objects[objects.size() - 1].accelerate(sf::Vector2f(0, 0));
//                    colors[objects.size() - 1] = color;
//                }
//            }
//
//            eventClock.restart();
//        }
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !objects.empty()) {
//            objects[0].accelerate((mousePos - objects[0].position) * 2000.0f);
//        }

//        objects[0].position.x = -200;
//        objects[0].position.y = 0;
//        objects[0].prevPosition.x = -200;
//        objects[0].prevPosition.y = 0;
//        objects[links.size()].position.x = -200 + links.size() * 20.0f;
//        objects[links.size()].position.y = 0;
//        objects[links.size()].prevPosition.x = -200 + links.size() * 20.0f;
//        objects[links.size()].prevPosition.y = 0;

        delta = clock.getElapsedTime().asSeconds();
        solver.update(objects, links, delta);
        clock.restart();

        window.clear(sf::Color(150, 150, 150));


        rect.setFillColor(sf::Color::Cyan);
        rect.setSize(sf::Vector2f(Solver::gridX * Solver::particleSize, Solver::gridY * Solver::particleSize));
        rect.setPosition(sf::Vector2f(0, 0));
        window.draw(rect);


        for (int i = 0; i < objects.size(); i++) {
            shape.setFillColor(sf::Color::Red);
            shape.setRadius(Solver::particleSize * 0.5f);
            shape.setOrigin(Solver::particleSize, Solver::particleSize);
            shape.setPosition(objects[i].position);
            shape.setFillColor(colors[i]);
            window.draw(shape);
        }


        std::cout << "Drawing grid" << std::endl;
        for (int i = 0; i < solver.gridVector->size(); ++i) {
            std::cout << "Drawing grid " << i << std::endl;
            sf::Color color = sf::Color(255,0,0,50);
            sf::VertexArray lines(sf::LinesStrip, 2);
            lines[0].position = sf::Vector2f(i * Solver::particleSize, 0);
            lines[0].color = color;
            lines[1].position = sf::Vector2f(i * Solver::particleSize, Solver::gridY * Solver::particleSize);
            lines[1].color = color;

            window.draw(lines);

            lines[0].position = sf::Vector2f(0, i * Solver::particleSize);
            lines[0].color = color;
            lines[1].position = sf::Vector2f(Solver::gridX * Solver::particleSize, i * Solver::particleSize);
            lines[1].color = color;

            window.draw(lines);
            for (int j = 0; j < solver.gridVector[i].size(); ++j) {
                text.setFillColor(color);
                text.setCharacterSize(8);
                text.setString(std::to_string(solver.gridVector[i][j].size()));
                text.setPosition(sf::Vector2f(i * Solver::particleSize, j * Solver::particleSize));
                window.draw(text);
            }
        }
//        for (auto &link: links) {
//            sf::VertexArray lines(sf::LinesStrip, 2);
//            lines[0].position = objects[link.object1].position;
//            lines[0].color = sf::Color::Green;
//            lines[1].position = objects[link.object2].position;
//            lines[1].color = sf::Color::Green;
//
//            window.draw(lines);
//        }
//        for (auto &link: links) {
//            sf::VertexArray lines(sf::LinesStrip, 2);
//            lines[0].position = objects[link.object1].position;
//            lines[0].color = sf::Color::Red;
//            lines[1].position = objects[link.object2].position;
//            lines[1].color = sf::Color::Red;
//
//            window.draw(lines);
//        }

//        String fpsText(std::to_string(fps));
//        text.setString(fpsText);
//        text.setPosition(-400, -350);
//        text.setCharacterSize(12);
//        window.draw(text);

        window.display();
    }
    return EXIT_SUCCESS;
}