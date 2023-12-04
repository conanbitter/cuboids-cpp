#include "proj.hpp"

Projectile::Projectile(AppWindow& app, Transform transform) : Figure(app, &SHAPE_PROJ, PROJ_SCALE, 1) {
    this->transform = transform;
}