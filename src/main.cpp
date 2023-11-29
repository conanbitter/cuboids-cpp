#include <iostream>
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"
#include "display/renderer.hpp"
#include "geometry.hpp"
#include "constants.hpp"

const Color colorWhite = Color{210, 210, 210, 255};

class Ship : public Figure {
   public:
    Ship(AppWindow& app) : Figure(app, &SHAPE_SHIP, SHIP_SCALE, 1) {}

    void update() {
        Vector2D speed(0, 0);
        if (app.isKeyPressed(KeyCode::KeyUp)) {
            speed += Vector2D(0, SHIP_MAX_SPEED);
        }
        if (app.isKeyPressed(KeyCode::KeyDown)) {
            speed += Vector2D(0, -SHIP_MAX_SPEED);
        }
        if (app.isKeyPressed(KeyCode::KeyLeft)) {
            speed += Vector2D(-SHIP_MAX_SPEED, 0);
        }
        if (app.isKeyPressed(KeyCode::KeyRight)) {
            speed += Vector2D(SHIP_MAX_SPEED, 0);
        }
        if (!speed.isZero()) {
            transform = transform.move(speed);
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