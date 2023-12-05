#include "constants.hpp"

Shape SHAPE_SHIP = Shape(true, {
                                   Vector2D(0.0, 1.2),
                                   Vector2D(0.7, -0.8),
                                   Vector2D(-0.7, -0.8),
                               });

Shape SHAPE_ASTER = Shape(true, {
                                    Vector2D(-1.0, -1.0),
                                    Vector2D(-1.0, 1.0),
                                    Vector2D(1.0, 1.0),
                                    Vector2D(1.0, -1.0),
                                });

Shape SHAPE_PROJ = Shape(true, {
                                   Vector2D(0.0, 0.8),
                                   Vector2D(0.2, 0.0),
                                   Vector2D(0.0, -1.2),
                                   Vector2D(-0.2, 0.0),
                               });

const float SHIP_SCALE = 0.1;
const float SHIP_MAX_SPEED = 0.1;
const float SHIP_ACCELERATION = 0.001;
const float SHIP_DRAG = 0.0001;
const float SHIP_ROT_SPEED = 0.05;

const float ASTER_SCALE = 0.2;
const float ASTER_KA = 0.0;
const float ASTER_KR = 0.0;
const float ASTER_KP = 0.0;
const float ASTER_KE = 0.0;
const std::array<Vector2D, 4> ASTER_CHILD_OFFSETS = {
    Vector2D(-0.5, -0.5),
    Vector2D(-0.5, 0.5),
    Vector2D(0.5, 0.5),
    Vector2D(0.5, -0.5)};

const float PROJ_SCALE = 0.05;
const float PROJ_SPEED = 0.01;

const double SHIP_SHOOTING_PERIOD = 1.5f;