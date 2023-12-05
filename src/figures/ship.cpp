#include "ship.hpp"
#include "proj.hpp"
#include <iostream>

void Ship::update() {
    Vector2D speed(0, 0);
    if (app.isKeyPressed(KeyCode::KeyUp)) {
        speed += Vector2D(0, 1);
    }
    if (app.isKeyPressed(KeyCode::KeyDown)) {
        speed += Vector2D(0, -1);
    }
    if (app.isKeyPressed(KeyCode::KeyLeft)) {
        speed += Vector2D(-1, 0);
    }
    if (app.isKeyPressed(KeyCode::KeyRight)) {
        speed += Vector2D(1, 0);
    }
    if (app.isKeyPressed(KeyCode::KeyA)) {
        shoot();
    }
    if (app.isKeyPressed(KeyCode::KeyB)) {
        transform = transform.rotate(0.05f);
    }
    if (app.isKeyPressed(KeyCode::KeyC)) {
        transform = transform.rotate(-0.05f);
    }
    if (!speed.isZero()) {
        speed = speed.toUnit() * 0.01;
        move(speed);
    }
    WrapFigure::update();
}

void Ship::collide(Figure& other) {
    color = Color{255, 20, 20, 255};
}

void Ship::shoot() {
    if (app.getTime() - lastShooted < SHIP_SHOOTING_PERIOD) {
        return;
    }

    Vector2D newPos = transform.offset + Vector2D::fromPolar(transform.angle, shootingPosition);
    man->add(std::make_unique<Projectile>(app, Transform(newPos, PROJ_SCALE, transform.angle)));
    lastShooted = app.getTime();
}