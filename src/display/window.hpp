#pragma once

#include <GLFW/glfw3.h>
#include <string>

enum class KeyCode { KeyLeft,
                     KeyRight,
                     KeyUp,
                     KeyDown,
                     KeyA,
                     KeyB,
                     KeyC };

class AppWindow {
   private:
    int windowWidth;
    int windowHeight;
    double prevTime;
    double elapsed;
    GLFWwindow* window;

    AppWindow(const AppWindow&) = delete;
    AppWindow& operator=(const AppWindow&) = delete;

   public:
    // Renderer gfx;

    AppWindow(const std::string title, int width, int height);
    void run();
    ~AppWindow();

    bool isKeyPressed(KeyCode key);
    void requestExit();
    void setTitle(std::string title);

    virtual void onLoad() {}
    virtual void onUnload() {}
    virtual void onUpdate() {}
    virtual void onDraw() {}
};