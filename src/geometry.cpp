#include "geometry.hpp"

Shape::Shape(bool closed, std::initializer_list<Vector2D> input) {
    float maxRadius = 0;
    for (Vector2D point : input) {
        float radius = point.length();
        if (radius > maxRadius) {
            maxRadius = radius;
        }
        points.push_back(point);
    }
    radius = maxRadius;
    if (closed) {
        points.push_back(points[0]);
    }
}