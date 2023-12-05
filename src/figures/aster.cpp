#include "aster.hpp"
#include <iostream>

Asteroid::Asteroid(AppWindow& app, float x, float y) : WrapFigure(app, &SHAPE_ASTER, ASTER_SCALE, 2) {
    move(Vector2D(x, y));
    transform = transform.rotate(0.1);
}

Asteroid::Asteroid(AppWindow& app, Transform transform, Vector2D speed, float rotSpeed) : WrapFigure(app, &SHAPE_ASTER, transform.scale, 2) {
    this->transform = transform;
    WrapFigure::update();
}

void Asteroid::collide(Figure& other) {
    state = FigureState::Delete;
    for (Vector2D offset : ASTER_CHILD_OFFSETS) {
        Transform newTransform = Transform(
            transform.apply(offset),
            transform.scale / 2.0f,
            transform.angle);

        Vector2D a = speed;
        Vector2D r = Vector2D(0, 0);
        Vector2D p = other.speed;
        Vector2D e = (offset * transform.scale).rotate(transform.angle);

        man->add(std::make_unique<Asteroid>(
            app,
            newTransform,
            a * ASTER_KA + r * ASTER_KR + p * ASTER_KP + e * ASTER_KE,
            0.0f));
    }
}