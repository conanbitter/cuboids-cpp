#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Ship : public WrapFigure {
   private:
    float shootingPosition;
    double lastShooted;

   public:
    Ship(AppWindow& app)
        : WrapFigure(app, &SHAPE_SHIP, SHIP_SCALE, 1),
          shootingPosition((SHAPE_SHIP.radius * SHIP_SCALE /*- SHAPE_PROJ.radius * PROJ_SCALE*/)),
          lastShooted(-SHIP_SHOOTING_PERIOD) {}

    void update() override;

    void collide(Figure& other) override;

    void shoot();
};