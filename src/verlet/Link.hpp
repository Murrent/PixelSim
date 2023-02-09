#pragma once


#include <vector>
#include <cstdlib>
#include <cstdint>
#include "VerletObject.hpp"
#include "VectorMath.hpp"

class Link {
public:
    uint32_t object1{};
    uint32_t object2{};
    float targetDistance{};

    virtual void apply(std::vector<VerletObject> &objects) {
//        VerletObject &obj1 = objects[object1];
//        VerletObject &obj2 = objects[object2];
//        const sf::Vector2f axis = obj1.position - obj2.position;
//        const float dist = Dist(sf::Vector2f(0, 0), axis);
//        const sf::Vector2f n = axis / dist;
//        const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
////
////        const float delta = targetDistance - dist;
////        obj1.position += scale * obj2.size * obj2.size * delta * n;
////        obj2.position -= scale * obj1.size * obj1.size * delta * n;
//        if (targetDistance < dist * 0.98f) {
//            const float delta = targetDistance - dist * 0.98f;
//            obj1.position += scale * obj2.size * obj2.size * delta * n;
//            obj2.position -= scale * obj1.size * obj1.size * delta * n;
//        } else if (targetDistance > dist * 1.02f) {
//            const float delta = targetDistance - dist * 1.02f;
//            obj1.position += scale * obj2.size * obj2.size * delta * n;
//            obj2.position -= scale * obj1.size * obj1.size * delta * n;
//        }
    }
};

class RotatorLink : public Link {
public:
    sf::Vector2f direction{0,1};

    void apply(std::vector<VerletObject> &objects) override {
        VerletObject &obj1 = objects[object1];
        VerletObject &obj2 = objects[object2];
        const sf::Vector2f axis = obj1.position - obj2.position;
        const float dist = Dist(sf::Vector2f(0, 0), axis);
        const sf::Vector2f mid = axis * 0.5f;
        //if (dist == 0.0f) return;
        //const sf::Vector2f n = (direction) / dist;
        //const float scale = 1 / (obj1.size * obj1.size + obj2.size * obj2.size);
        const sf::Vector2f desired1 = direction * targetDistance * 0.5f;
        const sf::Vector2f desired2 = -direction * targetDistance * 0.5f;
        const sf::Vector2f delta = direction * 0.5f;
        obj1.position += mid - delta;
        //obj2.position = mid - delta;
//        if (targetDistance < dist * 0.95f) {
//            const float delta = targetDistance - dist * 0.95f;
//            obj1.position += scale * obj2.size * obj2.size * delta * n;
//            obj2.position -= scale * obj1.size * obj1.size * delta * n;
//        } else if (targetDistance > dist * 1.05f) {
//            const float delta = targetDistance - dist * 1.05f;
//            obj1.position += scale * obj2.size * obj2.size * delta * n;
//            obj2.position -= scale * obj1.size * obj1.size * delta * n;
//        }
    }
};

class RigidObject {
    std::vector<uint32_t> objects;
    std::vector<float> distances;
    sf::Vector2f com;

    void calculateCOM(std::vector<VerletObject> &objs) {
        com = {};
        for (int i = 0; i < objects.size(); ++i) {
            com += objs[i].position;
        }
        com /= (float) objects.size();
    }

    void apply(std::vector<VerletObject> &objs) {

    }
};