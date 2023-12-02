#include <iostream>
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"
#include "display/renderer.hpp"
#include "geometry.hpp"
#include "constants.hpp"

const Color colorWhite = Color{210, 210, 210, 255};

class Ship : public WrapFigure {
   public:
    Ship(AppWindow& app) : WrapFigure(app, &SHAPE_SHIP, SHIP_SCALE, 1) {
        transform.angle = 0.5f;
    }

    void update() {
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

    void collide(Figure& other) {
        color = Color{255, 20, 20, 255};
        // std::cout << "Ship collide" << std::endl;
    }
};

class GameWindow : public AppWindow {
    FigureManager figureMan;

   public:
    GameWindow() : AppWindow("Cuboids", 800, 600) {
        figureMan.add(std::make_unique<Ship>(*this));
        PFigure cube = std::make_unique<Figure>(*this, &SHAPE_ASTER, 0.3f, 2);
        cube->move(Vector2D(0.5, 0));
        figureMan.add(std::move(cube));
    }

    void onDraw() {
        gfx.beginDraw(RenderType::Lines);
        figureMan.draw();
        gfx.endDraw();
    }

    void onUpdate() {
        figureMan.update();
    }
};

int main() {
    GameWindow game;
    game.run();
    return 0;
}