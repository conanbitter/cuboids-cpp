#pragma once

#include <vector>
#include <memory>
#include "vectors.hpp"
#include "display/window.hpp"

struct Shape {
    std::vector<Vector2D> points;
    float radius;

    Shape(bool closed, std::initializer_list<Vector2D> input);
};

struct Transform {
    Vector2D offset;
    float scale;
    float angle;

    Transform() : offset(0, 0), scale(1.0), angle(0) {}
    Transform(Vector2D offset, float scale, float angle) : offset(offset), scale(scale), angle(angle) {}
    Transform move(Vector2D distance) const;
    Transform rotate(float rotation) const;
    Vector2D apply(Vector2D point) const;
};

void drawGeometry(Renderer& renderer, const Shape& shape, const Transform& transform, Color color);

enum class FigureState {
    Active,
    Delete,
    Idle
};

class Figure {
   public:
    Shape* shape;
    Transform transform;
    Color color;
    AppWindow& app;
    float radius;
    FigureState state;
    int collisionGroup;

    Figure(AppWindow& app, Shape* shape, float scale, int collision);
    virtual void draw();
    virtual void update() {}
    void move(Vector2D offset);
};

typedef std::unique_ptr<Figure> PFigure;

class FigureManager {
   private:
    std::vector<PFigure> figures;

   public:
    void add(PFigure figure);
    void draw();
    void update();
};