#pragma once

#include "Scene.hpp"

class Game : public Scene {
public:
    void init() override;

    void update() override;

    void draw() override;

    void end() override;
};
