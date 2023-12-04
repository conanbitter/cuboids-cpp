#include "ship.hpp"

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
        color = Color{20, 255, 20, 255};
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
}

void Ship::collide(Figure& other) {
    color = Color{255, 20, 20, 255};
}

void Ship::draw() {
    WrapFigure::draw();
    Vector2D direction = Vector2D::fromPolar(transform.angle, radius);
    app.gfx.newLine();
    app.gfx.addPoint(transform.offset, Color{255, 255, 255, 255});
    app.gfx.addPoint(transform.offset + direction, Color{255, 2, 255, 255});
}