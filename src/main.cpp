#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"
#include "display/renderer.hpp"
#include "geometry.hpp"
#include "constants.hpp"

const Color colorWhite = Color{210, 210, 210, 255};

class GameWindow : public AppWindow {
    Figure ship;

   public:
    GameWindow() : AppWindow("Cuboids", 800, 600), ship(gfx, &SHAPE_SHIP, 0.1f) {}

    void onDraw() {
        gfx.beginDraw(RenderType::Lines);
        ship.draw();
        gfx.endDraw();
    }
};

int main() {
    GameWindow game;
    game.run();
    return 0;
}