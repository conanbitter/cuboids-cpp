#pragma once

#include "../geometry.hpp"
#include "../constants.hpp"

class Asteroid : public WrapFigure {
   public:
    Asteroid(AppWindow& app, float x, float y);
};