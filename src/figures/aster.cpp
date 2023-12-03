#include "aster.hpp"

Asteroid::Asteroid(AppWindow& app, float x, float y) : WrapFigure(app, &SHAPE_ASTER, 0.3f, 2) {
    move(Vector2D(x, y));
}