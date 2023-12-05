#include <iostream>
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"
#include "display/renderer.hpp"
#include "geometry.hpp"
#include "constants.hpp"
#include "figures/ship.hpp"
#include "figures/aster.hpp"

const Color colorWhite = Color{210, 210, 210, 255};

class GameWindow : public AppWindow {
    FigureManager figureMan;

   public:
    GameWindow() : AppWindow("Cuboids", 800, 600) {
        figureMan.add(std::make_unique<Ship>(*this));
        figureMan.add(std::make_unique<Asteroid>(*this, 1.0f, 0.0f));
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