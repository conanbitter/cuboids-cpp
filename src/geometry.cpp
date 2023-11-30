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

Figure::Figure(AppWindow& app, Shape* shape, float scale = 1.0f, int collision = 0)
    : app(app), shape(shape), collisionGroup(collision) {
    transform.scale = scale;
    color = Color{200, 200, 200, 255};
    radius = shape->radius * scale;
    state = FigureState::Active;
}

void Figure::draw() {
    drawGeometry(app.gfx, shape, transform, color);
}

void Figure::move(Vector2D offset) {
    transform = transform.move(offset);
}

void WrapFigure::move(Vector2D offset) {
    Figure::move(offset);
    Vector2D bounds = app.gfx.getBounds();
    float thickness = app.gfx.getThickness();
    if (transform.offset.x > bounds.x) {
        transform.offset.x -= bounds.x * 2;
    }
    if (transform.offset.x < -bounds.x) {
        transform.offset.x += bounds.x * 2;
    }
    if (transform.offset.y > bounds.y) {
        transform.offset.y -= bounds.y * 2;
    }
    if (transform.offset.y < -bounds.y) {
        transform.offset.y += bounds.y * 2;
    }

    if (transform.offset.x + radius + thickness > bounds.x) {
        xcopy = -1;
    } else if (transform.offset.x - radius - thickness < -bounds.x) {
        xcopy = 1;
    } else {
        xcopy = 0;
    }

    if (transform.offset.y + radius + thickness > bounds.y) {
        ycopy = -1;
    } else if (transform.offset.y - radius - thickness < -bounds.y) {
        ycopy = 1;
    } else {
        ycopy = 0;
    }
}

void WrapFigure::draw() {
    drawGeometry(app.gfx, shape, transform, color);
    if (xcopy != 0) {
        drawGeometry(app.gfx, shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, 0)), color);
        if (ycopy != 0) {
            drawGeometry(app.gfx, shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, ycopy * app.gfx.getBounds().y * 2)), color);
        }
    }
    if (ycopy != 0) {
        drawGeometry(app.gfx, shape, transform.move(Vector2D(0, ycopy * app.gfx.getBounds().y * 2)), color);
    }
}

void FigureManager::add(PFigure figure) {
    figures.push_back(std::move(figure));
}

void FigureManager::draw() {
    for (auto& figure : figures) {
        if (figure->state == FigureState::Active) {
            figure->draw();
        }
    }
}

void FigureManager::update() {
    for (auto& figure : figures) {
        if (figure->state == FigureState::Active) {
            figure->update();
        }
    }
    for (size_t i = 0; i < figures.size(); i++) {
        if (figures[i]->state == FigureState::Delete) {
            figures[i] = std::move(figures.back());
            figures.pop_back();
        }
    }
}