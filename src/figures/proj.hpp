#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Projectile : public Figure {
   public:
    Projectile(AppWindow& app, Transform transform);
    void update() override;
    void collide(Figure& other) override;
};