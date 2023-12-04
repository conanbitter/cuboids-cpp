#include "aster.hpp"

Asteroid::Asteroid(AppWindow& app, float x, float y) : WrapFigure(app, &SHAPE_ASTER, ASTER_SCALE, 2) {
    move(Vector2D(x, y));
}