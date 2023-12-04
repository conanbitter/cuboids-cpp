#include <glad/gl.h>
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

const double TICK_RATE = 1.0 / 60.0;

const int keymap[] = {
    GLFW_KEY_LEFT,
    GLFW_KEY_RIGHT,
    GLFW_KEY_UP,
    GLFW_KEY_DOWN,
    GLFW_KEY_Z,
    GLFW_KEY_X,
    GLFW_KEY_C};

void sizeCallback(GLFWwindow* window, int width, int height) {
    Renderer* renderer = (Renderer*)(glfwGetWindowUserPointer(window));
    renderer->setViewport(width, height);
}

AppWindow::AppWindow(const std::string title, int width, int height) {
    if (!glfwInit())
        std::cout << "Failed to initialize GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    int screenWidth = videoMode->width;
    int screenHeight = videoMode->height;

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
    }
    glfwSetWindowPos(window, (screenWidth - width) / 2, (screenHeight - height) / 2);

    glfwMakeContextCurrent(window);

    gfx.init();
    gfx.setViewport(width, height);

    glfwSetWindowUserPointer(window, &gfx);
    glfwSetWindowSizeCallback(window, sizeCallback);
    elapsed = 0.0;
    prevTime = glfwGetTime();
}

void AppWindow::run() {
    onLoad();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            requestExit();
        }

        double newTime = glfwGetTime();
        elapsed += newTime - prevTime;
        prevTime = newTime;
        while (elapsed > TICK_RATE) {
            onUpdate();
            elapsed -= TICK_RATE;
        }

        gfx.startRender();
        onDraw();
        gfx.finishRender();
        glfwSwapBuffers(window);
    }

    onUnload();
}

AppWindow::~AppWindow() {
    gfx.free();
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool AppWindow::isKeyPressed(KeyCode key) {
    return glfwGetKey(window, keymap[(int)key]) == GLFW_PRESS;
}

void AppWindow::setTitle(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void AppWindow::requestExit() {
    glfwSetWindowShouldClose(window, 1);
}

double AppWindow::getTime() {
    return glfwGetTime();
}