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
    sf::Vector2f gravity = {0.0f, 400.0f};
    std::vector<std::vector<uint32_t>> gridVector;
    std::vector<std::pair<uint32_t, uint32_t>> pairs;
    const int gridSize = 800;
    const int gridSlotSize = 10;
    const int loopLength = gridSize / gridSlotSize;
    const sf::Vector2i gridStart{int(-gridSize * 0.5f), int(-gridSize * 0.5f)};

    void start() {
        std::cout << "loop length: " << loopLength << std::endl;
        gridVector.resize(loopLength * loopLength);
    }

    void update(std::vector<VerletObject> &objects, std::vector<Link> &links, float dt) {
        const uint32_t subSteps = 8;
        const float subStepsMultiplier = 1.0f / (float) subSteps;
        const float delta = dt * subStepsMultiplier;
        for (int i = 0; i < subSteps; ++i) {
            applyGravity(objects);
            for (auto &link: links) {
                link.apply(objects);
            }
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
        const sf::Vector2f position(0, 0);
        const float radius = 300.0f;

        for (auto &obj: objects) {
            if (obj.staticBody) continue;
            const sf::Vector2f normal = Normal(obj.position, position);
            //std::cout << normal.x << " " << normal.y << std::endl;
            const sf::Vector2f to_obj = obj.position - position;
            const float dist = Dist(sf::Vector2f(0, 0), to_obj);
            if (dist > radius - obj.size) {
                const sf::Vector2f n = to_obj / dist;
                obj.position = position + n * (300.0f - obj.size);// normal * (300.0f - obj.size);
                //obj.prevPosition = obj.position;
            }
        }
    }

    void solveCollisions(std::vector<VerletObject> &objects) {
        //std::cout << "Clearing..." << std::endl;
        for (auto &slot: gridVector) {
            slot.clear();
        }
        pairs.clear();
        //std::cout << "Filling..." << std::endl;
        const uint32_t count = objects.size();
        for (uint32_t i = 0; i < count; ++i) {
            auto &obj = objects[i];
            const float left = obj.position.x - gridStart.x - obj.size;
            const float top = obj.position.y - gridStart.x- obj.size;
            const float right = left + obj.size * 2;
            const float bottom = top + obj.size * 2;
            const int iLeft = std::floor(left / (float) gridSlotSize);
            const int iTop = std::floor(top / (float) gridSlotSize);
            const int iRight = std::floor(right / (float) gridSlotSize);
            const int iBottom = std::floor(bottom / (float) gridSlotSize);
            //std::cout << "Filling 1: " << iLeft + iTop * loopLength << std::endl;
            gridVector[iLeft + iTop * loopLength].push_back(i);
            bool diffX = false, diffY = false;
            if (iLeft != iRight) {
                //std::cout << "Filling 2: " << iRight + iTop * loopLength << std::endl;
                gridVector[iRight + iTop * loopLength].push_back(i);
                diffX = true;
            }
            if (iTop != iBottom) {
                //std::cout << "Filling 3: " << iLeft + iBottom * loopLength << std::endl;
                gridVector[iLeft + iBottom * loopLength].push_back(i);
                diffY = true;
            }
            if (diffX && diffY) {
                //std::cout << "Filling 4: " << iRight + iBottom * loopLength << std::endl;
                gridVector[iRight + iBottom * loopLength].push_back(i);
            }
        }

        //std::cout << "Calculating..." << std::endl;
        for (auto &slot: gridVector) {
            if (slot.size() < 2) continue;
            for (int i = 0; i < slot.size(); ++i) {
                auto &obj1 = objects[slot[i]];
                for (int j = i + 1; j < slot.size(); ++j) {
                    bool hasPair = false;
                    for (auto& pair:pairs) {
                        if ((pair.first == i && pair.second == j) || (pair.first == j && pair.second == i)){
                            hasPair = true;
                            break;
                        }
                    }
                    if (hasPair) continue;

                    auto &obj2 = objects[slot[j]];
                    const sf::Vector2f axis = obj1.position - obj2.position;
                    const float distSqr = SqrDist(obj1.position, obj2.position);
                    const float fullSize = (obj1.size + obj2.size);
                    if (distSqr < fullSize * fullSize) {
                        const float dist = std::sqrt(distSqr);
                        const sf::Vector2f n = axis / dist;
                        const float delta = fullSize - dist;
                        const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
                        // Scale was initially 0.5f but this was changed to make larger objects move less by small objects
                        const sf::Vector2f endScale = scale * delta * n;
                        if (!obj1.staticBody)
                            obj1.position += endScale * obj2.size * obj2.size;
                        if (!obj2.staticBody)
                            obj2.position -= endScale * obj1.size * obj1.size;
                    }

                }
            }
        }
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

