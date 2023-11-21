#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"
#include "display/renderer.hpp"

const Color colorWhite = Color{210, 210, 210, 255};

class GameWindow : public AppWindow {
   public:
    GameWindow() : AppWindow("Cuboids", 800, 600) {}
    void onDraw() {
        gfx.beginDraw(RenderType::Lines);
        gfx.addPoint(Vector2D(-0.5, -0.5), colorWhite);
        gfx.addPoint(Vector2D(0.0, 0.5), colorWhite);
        gfx.addPoint(Vector2D(0.5, -0.5), colorWhite);
        gfx.addPoint(Vector2D(-0.5, -0.5), colorWhite);
        gfx.newLine();
        gfx.addPoint(Vector2D(-0.5, 0.5), colorWhite);
        gfx.addPoint(Vector2D(0.5, 0.5), colorWhite);
        gfx.endDraw();
    }
};

int main() {
    GameWindow game;
    game.run();
    return 0;
}