#pragma once

#include <vector>
#include "vectors.hpp"

struct Shape {
    std::vector<Vector2D> points;
    float radius;

    Shape(bool closed, std::initializer_list<Vector2D> input);
};