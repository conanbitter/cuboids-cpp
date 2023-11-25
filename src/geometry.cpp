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

Transform Transform::move(Vector2D distance) const {
    return Transform(offset + distance, scale, angle);
}
Transform Transform::rotate(float rotation) const {
    return Transform(offset, scale, angle + rotation);
}

Vector2D Transform::apply(Vector2D point) const {
    return point.rotate(angle) * scale + offset;
}

void drawGeometry(Renderer& renderer, const Shape* shape, const Transform& transform, Color color) {
    renderer.newLine();
    for (Vector2D point : shape->points) {
        renderer.addPoint(transform.apply(point), color);
    }
}

Figure::Figure(Renderer& renderer, Shape* shape, float scale = 1.0f) : renderer(renderer), shape(shape) {
    transform.scale = scale;
    color = Color{200, 200, 200, 255};
    radius = shape->radius * scale;
}

void Figure::draw() {
    drawGeometry(renderer, shape, transform, color);
}

void Figure::move(Vector2D offset) {
    transform = transform.move(offset);
}