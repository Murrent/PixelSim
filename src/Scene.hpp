#pragma once


class Scene {
public:
    Scene() = default;

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void end() = 0;
};
