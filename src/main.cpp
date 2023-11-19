#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "display/window.hpp"

class GameWindow : public AppWindow {
   public:
    GameWindow() : AppWindow("Cuboids", 800, 600) {}
};

int main() {
    GameWindow game;
    game.run();
    return 0;
}