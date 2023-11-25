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

Transform Transform::move(Vector2D distance) {
    return Transform(offset + distance, scale, angle);
}
Transform Transform::rotate(float rotation) {
    return Transform(offset, scale, angle + rotation);
}

Vector2D Transform::apply(Vector2D point) {
    return point.rotate(angle) * scale + offset;
}