#include "proj.hpp"

Projectile::Projectile(AppWindow& app, Transform transform) : Figure(app, &SHAPE_PROJ, 0.3f, 1) {
    this->transform = transform;
}