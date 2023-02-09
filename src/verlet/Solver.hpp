#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include "VerletObject.hpp"
#include "VectorMath.hpp"
#include "Link.hpp"

// CURRENT PROBLEM:
// solveCollisions() sometimes cause multiple resolutions on the same two objects!!!

class Solver {
public:
    sf::Vector2f gravity = {0.0f, 10.0f};
    std::vector<std::vector<std::vector<uint32_t>>> *gridVector = new std::vector<std::vector<std::vector<uint32_t>>>();
    static constexpr uint32_t particleSize = 1, gridX = 10, gridY = 10;
    static constexpr uint32_t subSteps = 8;
    static constexpr float subStepsMultiplier = 1.0f / (float) subSteps;;

    void start() {
        gridVector->resize(gridX);
        for (auto &slot: *gridVector) {
            slot.resize(gridY);
        }
    }

    void update(std::vector<VerletObject> &objects, std::vector<Link> &links, float dt) {
        const float delta = dt * subStepsMultiplier;
        for (int i = 0; i < subSteps; ++i) {
            applyGravity(objects);
//            for (auto &link: links) {
//                link.apply(objects);
//            }
            applyConstraint(objects);
            solveCollisions(objects);
            updatePositions(objects, delta);
        }
    }

    void updatePositions(std::vector<VerletObject> &objects, float dt) {
        for (auto &obj: objects) {
            obj.updatePos(dt);
        }
    }

    void applyGravity(std::vector<VerletObject> &objects) {
        for (auto &obj: objects) {
            obj.accelerate(gravity);
        }
    }

    void applyConstraint(std::vector<VerletObject> &objects) {
        for (auto &obj: objects) {
            if (obj.staticBody) continue;
            if (obj.position.x < particleSize) {
                float temp = obj.prevPosition.x;
                obj.prevPosition.x = obj.position.x;
                obj.position.x = temp;
            }
            if (obj.position.x > gridX * particleSize) {
                float temp = obj.prevPosition.x;
                obj.prevPosition.x = obj.position.x;
                obj.position.x = temp;
            }
            if (obj.position.y < particleSize) {
                float temp = obj.prevPosition.y;
                obj.prevPosition.y = obj.position.y;
                obj.position.y = temp;
            }
            if (obj.position.y > gridY * particleSize) {
                float temp = obj.prevPosition.y;
                obj.prevPosition.y = obj.position.y;
                obj.position.y = temp;
            }
        }
    }

    void solveCollisions(std::vector<VerletObject> &objects) {
        std::cout << "Clearing..." << std::endl;
        for (auto &row: *gridVector) {
            for (auto &particles: row) {
                particles.clear();
            }
        }
        std::cout << "Filling..." << std::endl;
        const uint32_t count = objects.size();
        for (uint32_t i = 0; i < count; ++i) {
            auto &obj = objects[i];
            const sf::Vector2f pos = obj.position;
            const uint32_t x = (uint32_t) (pos.x / particleSize);
            const uint32_t y = (uint32_t) (pos.y / particleSize);
            if (x >= gridX || y >= gridY) continue;
            (*gridVector)[x][y].push_back(i);
        }

        //std::cout << "Calculating..." << std::endl;
//        for (auto &slot: gridVector) {
//            if (slot.size() < 2) continue;
//            for (int i = 0; i < slot.size(); ++i) {
//                auto &obj1 = objects[slot[i]];
//                for (int j = i + 1; j < slot.size(); ++j) {
//                    bool hasPair = false;
//                    for (auto& pair:pairs) {
//                        if ((pair.first == i && pair.second == j) || (pair.first == j && pair.second == i)){
//                            hasPair = true;
//                            break;
//                        }
//                    }
//                    if (hasPair) continue;
//
//                    auto &obj2 = objects[slot[j]];
//                    const sf::Vector2f axis = obj1.position - obj2.position;
//                    const float distSqr = SqrDist(obj1.position, obj2.position);
//                    const float fullSize = (obj1.size + obj2.size);
//                    if (distSqr < fullSize * fullSize) {
//                        const float dist = std::sqrt(distSqr);
//                        const sf::Vector2f n = axis / dist;
//                        const float delta = fullSize - dist;
//                        const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
//                        // Scale was initially 0.5f but this was changed to make larger objects move less by small objects
//                        const sf::Vector2f endScale = scale * delta * n;
//                        if (!obj1.staticBody)
//                            obj1.position += endScale * obj2.size * obj2.size;
//                        if (!obj2.staticBody)
//                            obj2.position -= endScale * obj1.size * obj1.size;
//                    }
//
//                }
//            }
//        }
//        uint32_t count = objects.size();
//        for (uint32_t i = 0; i < count; ++i) {
//            auto &obj1 = objects[i];
//            for (uint32_t k = i + 1; k < count; ++k) {
//                auto &obj2 = objects[k];
//                const sf::Vector2f axis = obj1.position - obj2.position;
//                const float dist = Dist(sf::Vector2f(0, 0), axis);
//                if (dist < obj1.size + obj2.size) {
//                    const sf::Vector2f n = axis / dist;
//                    const float delta = (obj1.size + obj2.size) - dist;
//                    const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
//                    // Scale was initially 0.5f but this was changed to make larger objects move less by small objects
//                    if (!obj1.staticBody)
//                        obj1.position += scale * obj2.size * obj2.size * delta * n;
//                    if (!obj2.staticBody)
//                        obj2.position -= scale * obj1.size * obj1.size * delta * n;
//                }
//
//            }
//        }


    }
};

