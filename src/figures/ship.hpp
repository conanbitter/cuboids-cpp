#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Ship : public WrapFigure {
   public:
    Ship(AppWindow& app) : WrapFigure(app, &SHAPE_SHIP, SHIP_SCALE, 1) {}

    void update() override;

    void collide(Figure& other) override;

    void draw() override;
};