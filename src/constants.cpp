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

const float PROJ_SCALE = 0.05;
const float PROJ_SPEED = 0.01;