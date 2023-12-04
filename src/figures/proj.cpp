#include "proj.hpp"

Projectile::Projectile(AppWindow& app, Transform transform) : Figure(app, &SHAPE_PROJ, PROJ_SCALE, 1) {
    this->transform = transform;
    speed = Vector2D::fromPolar(transform.angle, PROJ_SPEED);
}

void Projectile::update() {
    Figure::update();
    Vector2D bounds = app.gfx.getBounds();
    float thickness = app.gfx.getThickness();
    float xbound = bounds.x + radius + thickness;
    float ybound = bounds.y + radius + thickness;

    if ((transform.offset.x > xbound) ||
        (transform.offset.x < -xbound) ||
        (transform.offset.y > ybound) ||
        (transform.offset.y < -ybound)) {
        state = FigureState::Delete;
    }
}

void Projectile::collide(Figure& other) {
    state = FigureState::Delete;
}