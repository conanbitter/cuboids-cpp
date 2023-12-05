#include "aster.hpp"
#include <iostream>

Asteroid::Asteroid(AppWindow& app, float x, float y) : WrapFigure(app, &SHAPE_ASTER, ASTER_SCALE, 2) {
    move(Vector2D(x, y));
    level = 1;
    transform = transform.rotate(0.1);
    rotationSpeed = 0.01;
    speed = Vector2D(0.005, 0.001);
}

Asteroid::Asteroid(AppWindow& app, Transform transform, Vector2D speed, float rotSpeed, int level)
    : WrapFigure(app, &SHAPE_ASTER, transform.scale, 2),
      rotationSpeed(rotSpeed),
      level(level) {
    this->transform = transform;
    this->speed = speed;
    updateCopies();
}

void Asteroid::update() {
    WrapFigure::update();
    transform = transform.rotate(rotationSpeed);
}

void Asteroid::collide(Figure& other) {
    state = FigureState::Delete;
    if (level >= ASTER_MAX_LEVEL) {
        return;
    }

    for (Vector2D offset : ASTER_CHILD_OFFSETS) {
        Transform newTransform = Transform(
            transform.apply(offset),
            transform.scale / 2.0f,
            transform.angle);

        Vector2D a = speed;
        Vector2D e = (offset * transform.scale).rotate(transform.angle);
        Vector2D r = e - (offset * transform.scale).rotate(transform.angle - rotationSpeed);
        Vector2D p = other.speed;
        Vector2D newSpeed = a * ASTER_KA + r * ASTER_KR + p * ASTER_KP + e * ASTER_KE;

        man->add(std::make_unique<Asteroid>(
            app,
            newTransform,
            newSpeed.toUnit() * 0.005,
            rotationSpeed * ASTER_ROT_ACCEL,
            level + 1));
    }
}