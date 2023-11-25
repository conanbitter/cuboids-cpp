#pragma once

#include <vector>
#include "vectors.hpp"

struct Shape {
    std::vector<Vector2D> points;
    float radius;

    Shape(bool closed, std::initializer_list<Vector2D> input);
};

struct Transform {
    Vector2D offset;
    float scale;
    float angle;

    Transform() : offset(0, 0), scale(1.0), angle(0) {}
    Transform(Vector2D offset, float scale, float angle) : offset(offset), scale(scale), angle(angle) {}
    Transform move(Vector2D distance);
    Transform rotate(float rotation);
    Vector2D apply(Vector2D point);
};