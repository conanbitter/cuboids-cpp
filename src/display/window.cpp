#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glad/gl.h>

void sizeCallback(GLFWwindow* window, int width, int height) {
    // Renderer* renderer = (Renderer*)(glfwGetWindowUserPointer(window));
    // renderer->setViewport(width, height);
}

AppWindow::AppWindow(const std::string title, int width, int height) {
    if (!glfwInit())
        std::cout << "Failed to initialize GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
    }
    std::cout << "OpenGL version " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
}

void AppWindow::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

AppWindow::~AppWindow() {
    glfwTerminate();
}

bool AppWindow::isKeyPressed(KeyCode key) {
}

void AppWindow::setTitle(std::string title) {
}