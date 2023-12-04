#include "geometry.hpp"
#include <iostream>

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

bool checkShapeCollision(const Shape& shape1, const Transform& transform1, const Shape& shape2, const Transform& transform2) {
    // Simple distance checking
    float distance = transform1.offset.distance(transform2.offset);
    if (distance > (shape1.radius * transform1.scale + shape2.radius * transform2.scale)) {
        return false;
    }

    // Using "http://content.gpwiki.org/index.php/Polygon_Collision"
    // (http://web.archive.org/web/20141127210836/http://content.gpwiki.org/index.php/Polygon_Collision)
    // Assuming both figures are convex polygons

    for (int i = 0; i < shape1.points.size() - 1; i++) {
        Vector2D v1 = transform1.apply(shape1.points[i + 1]) - transform1.apply(shape1.points[i]);
        bool outside = true;
        for (const Vector2D& point : shape2.points) {
            Vector2D v2 = transform2.apply(point) - transform1.apply(shape1.points[i]);
            if (v1.pseudoCross(v2) < 0) {
                outside = false;
                break;
            }
        }
        if (outside) {
            return false;
        }
    }

    for (int i = 0; i < shape2.points.size() - 1; i++) {
        Vector2D v1 = transform2.apply(shape2.points[i + 1]) - transform2.apply(shape2.points[i]);
        bool outside = true;
        for (const Vector2D& point : shape1.points) {
            Vector2D v2 = transform1.apply(point) - transform2.apply(shape2.points[i]);
            if (v1.pseudoCross(v2) < 0) {
                outside = false;
                break;
            }
        }
        if (outside) {
            return false;
        }
    }
    return true;
}

Figure::Figure(AppWindow& app, Shape* shape, float scale = 1.0f, int collision = 0)
    : app(app), shape(shape), collisionGroup(collision), speed(0, 0) {
    transform.scale = scale;
    color = Color{200, 200, 200, 255};
    radius = shape->radius * scale;
    state = FigureState::Active;
}

void Figure::draw() {
    drawGeometry(app.gfx, shape, transform, color);
}

void Figure::update() {
    move(speed);
}

void Figure::move(Vector2D offset) {
    transform = transform.move(offset);
}

bool Figure::sendCollision(Figure& other) {
    return other.receiveCollision(*shape, transform);
}

bool Figure::receiveCollision(const Shape& otherShape, const Transform& otherTransform) {
    return checkShapeCollision(otherShape, otherTransform, *shape, transform);
}

void WrapFigure::update() {
    Figure::update();
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

bool WrapFigure::sendCollision(Figure& other) {
    if (other.receiveCollision(*shape, transform)) {
        return true;
    }
    if (xcopy != 0) {
        if (other.receiveCollision(*shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, 0)))) {
            return true;
        }
        if (ycopy != 0) {
            if (other.receiveCollision(*shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, ycopy * app.gfx.getBounds().y * 2)))) {
                return true;
            }
        }
    }
    if (ycopy != 0) {
        if (other.receiveCollision(*shape, transform.move(Vector2D(0, ycopy * app.gfx.getBounds().y * 2)))) {
            return true;
        }
    }
    return false;
}

bool WrapFigure::receiveCollision(const Shape& otherShape, const Transform& otherTransform) {
    if (checkShapeCollision(otherShape, otherTransform, *shape, transform)) {
        return true;
    }
    if (xcopy != 0) {
        if (checkShapeCollision(otherShape, otherTransform, *shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, 0)))) {
            return true;
        }
        if (ycopy != 0) {
            if (checkShapeCollision(otherShape, otherTransform, *shape, transform.move(Vector2D(xcopy * app.gfx.getBounds().x * 2, ycopy * app.gfx.getBounds().y * 2)))) {
                return true;
            }
        }
    }
    if (ycopy != 0) {
        if (checkShapeCollision(otherShape, otherTransform, *shape, transform.move(Vector2D(0, ycopy * app.gfx.getBounds().y * 2)))) {
            return true;
        }
    }
    return false;
}

void FigureManager::add(PFigure figure) {
    figure->man = this;
    accum.push_back(std::move(figure));
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
    checkCollisions();
    for (size_t i = 0; i < figures.size(); i++) {
        if (figures[i]->state == FigureState::Delete) {
            figures[i] = std::move(figures.back());
            figures.pop_back();
        }
    }
    if (accum.size() > 0) {
        figures.insert(figures.end(), std::make_move_iterator(accum.begin()), std::make_move_iterator(accum.end()));
        accum.clear();
    }
}

void FigureManager::checkCollisions() {
    for (int i = 0; i < figures.size(); i++) {
        for (int j = i + 1; j < figures.size(); j++) {
            if (figures[i]->collisionGroup == figures[j]->collisionGroup) {
                continue;
            }
            if (figures[i]->sendCollision(*figures[j])) {
                figures[i]->collide(*figures[j]);
                figures[j]->collide(*figures[i]);
            }
        }
    }
}
