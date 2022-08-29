#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace sf;

Vector2f Normal(Vector2f a, Vector2f b) {
    float diffX = (a.x - b.x);
    float diffY = (a.y - b.y);
    float h = std::sqrt(diffX * diffX + diffY * diffY);
    return Vector2f((diffX) / h, (diffY) / h);
}

float Dist(Vector2f a, Vector2f b) {
    float distX = a.x - b.x;
    float distY = a.y - b.y;
    return std::sqrt((distX * distX) + (distY * distY));
}


float SqrDist(Vector2f a, Vector2f b) {
    float distX = a.x - b.x;
    float distY = a.y - b.y;
    return (distX * distX) + (distY * distY);
}

// POINT/CIRCLE
bool PointCircle(Vector2f &p, Vector2f &c, float r) {
    float distance = SqrDist(p, c);

    if (distance <= r * r) {
        return true;
    }
    return false;
}

// LINE/POINT
// Maybe possible to optimize to use SqrDist
bool LinePoint(Vector2f &a, Vector2f &b, Vector2f &p) {

    // get distance from the point to the two ends of the line
    float d1 = Dist(p, a);
    float d2 = Dist(p, b);

    // get the length of the line
    float lineLen = Dist(a, b);

    // since floats are so minutely accurate, add
    // a little buffer zone that will give collision
    float buffer = 0.1;    // higher # = less accurate

    // if the two distances are equal to the line's
    // length, the point is on the line!
    // note we use the buffer here to give a range,
    // rather than one #
    if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
        return true;
    }
    return false;
}

Vector2f LineLine(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    float uA = ((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) /
               ((d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y));
    float uB = ((b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x)) /
               ((d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y));

    if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        float intersectionX = a.x + (uA * (b.x - a.x));
        float intersectionY = a.y + (uA * (b.y - a.y));

        return Vector2f(intersectionX, intersectionY);
    }
    return Vector2f(0, 0);
}
