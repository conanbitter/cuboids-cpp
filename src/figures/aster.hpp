#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Asteroid : public WrapFigure {
   public:
    Asteroid(AppWindow& app, float x, float y);
    Asteroid(AppWindow& app, Transform transform, Vector2D speed, float rotSpeed);

    void collide(Figure& other) override;
};