#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Asteroid : public WrapFigure {
   private:
    int level;
    float rotationSpeed;

   public:
    Asteroid(AppWindow& app, float x, float y);
    Asteroid(AppWindow& app, Transform transform, Vector2D speed, float rotSpeed, int level);

    void update() override;
    void collide(Figure& other) override;
};