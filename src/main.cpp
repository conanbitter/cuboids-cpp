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
    Ship(AppWindow& app) : WrapFigure(app, &SHAPE_SHIP, SHIP_SCALE, 1) {}

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
        if (!speed.isZero()) {
            speed = speed.toUnit() * 0.01;
            move(speed);
        }
    }
};

class GameWindow : public AppWindow {
    FigureManager figureMan;

   public:
    GameWindow() : AppWindow("Cuboids", 800, 600) {
        figureMan.add(std::make_unique<Ship>(*this));
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