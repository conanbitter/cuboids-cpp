#pragma once

#include "geometry.hpp"
#include "vectors.hpp"
#include <array>

extern Shape SHAPE_SHIP;

extern Shape SHAPE_ASTER;

extern Shape SHAPE_PROJ;

extern const float SHIP_SCALE;
extern const float SHIP_MAX_SPEED;
extern const float SHIP_ACCELERATION;
extern const float SHIP_DRAG;
extern const float SHIP_ROT_SPEED;
extern const double SHIP_SHOOTING_PERIOD;

extern const float ASTER_SCALE;
extern const float ASTER_KA;
extern const float ASTER_KR;
extern const float ASTER_KP;
extern const float ASTER_KE;
extern const std::array<Vector2D, 4> ASTER_CHILD_OFFSETS;
constexpr int ASTER_MAX_LEVEL = 4;
extern const float ASTER_ROT_ACCEL;
extern const std::array<float, ASTER_MAX_LEVEL + 1> ASTER_MAX_SPEED;
extern const float ASTER_SPEED_DAMPING;

extern const float PROJ_SCALE;
extern const float PROJ_SPEED;