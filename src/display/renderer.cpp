#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

const float MAX_LINE_THICKNESS = 5.0f;
const float MIN_LINE_THICKNESS = 1.0f;

const char* vertexShaderCode = R"(
    #version 150

    uniform float ar;

    in vec2 vert;
    in vec4 vertColor;

    out vec4 fragColor;

    void main() {
        gl_Position = vec4(vert.x / ar, vert.y, 0.0, 1.0);
        fragColor = vertColor;
    }
)";

const char* fragmentShaderCode = R"(
    #version 150

    in vec4 fragColor;

    out vec4 outputColor;

    void main() {
        outputColor = fragColor;
    }
)";

void Renderer::init() {
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
    }
    std::cout << "OpenGL version " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;

    // Set properties
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glDisable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Init shader
    program = compileShaderProgram(vertexShaderCode, fragmentShaderCode);
    glUseProgram(program);
    arLocation = glGetUniformLocation(program, "ar");
    GLint vert_loc = glGetAttribLocation(program, "vert");
    GLint col_loc = glGetAttribLocation(program, "vertColor");

    // Init buffers
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray((GLuint)vert_loc);
    glVertexAttribPointer((GLuint)vert_loc, 2, GL_FLOAT, false, (GLsizei)sizeof(Vertex), nullptr);
    glEnableVertexAttribArray((GLuint)col_loc);
    glVertexAttribPointer((GLuint)col_loc, 4, GL_UNSIGNED_BYTE, true, (GLsizei)sizeof(Vertex), (const void*)(sizeof(Vector2D)));

    glUniform1f(arLocation, 1.0);
}

void Renderer::free() {
    if (glIsBuffer(vbo)) {
        glDeleteBuffers(1, &vbo);
    }

    if (glIsVertexArray(vao)) {
        glDeleteVertexArrays(1, &vao);
    }

    if (glIsProgram(program)) {
        glDeleteProgram(program);
    }
}

void Renderer::startRender() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    state = RendererState::Ready;
}

void Renderer::beginDraw(RenderType renderType) {
    if (state == RendererState::NotReady) {
        return;
    }
    vertices.clear();
    switch (renderType) {
        case RenderType::Points:
            state = RendererState::DrawingPoints;
            break;
        case RenderType::Lines:
            state = RendererState::DrawingLines;
            isNewLine = true;
            break;
    }
}

void Renderer::addPoint(Vector2D pos, Color color) {
    Vertex newVertex{pos = pos, color = color};
    if (state == RendererState::DrawingPoints) {
        vertices.push_back(newVertex);
    } else if (state == RendererState::DrawingLines) {
        if (isNewLine) {
            isNewLine = false;
        } else {
            vertices.push_back(lastVertex);
            vertices.push_back(newVertex);
        }
        lastVertex = newVertex;
    }
}

void Renderer::endDraw() {
    GLenum drawType = GL_KEEP;  // a dummy value
    if (state == RendererState::DrawingPoints) {
        drawType = GL_POINTS;
    } else if (state == RendererState::DrawingLines) {
        drawType = GL_LINES;
    }
    if (drawType != GL_KEEP) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(drawType, 0, vertices.size());
        state = RendererState::Ready;
    }
}

void Renderer::finishRender() {
    state = RendererState::NotReady;
}

const float thickRate = 1080.0 / 3.0;

void Renderer::setViewport(int width, int height) {
    glViewport(0, 0, width, height);
    float newAr = (float)width / (float)height;
    glUniform1f(arLocation, newAr);
    float newThickness = (float)height / thickRate;
    if (newThickness < MIN_LINE_THICKNESS) {
        newThickness = MIN_LINE_THICKNESS;
    }
    if (newThickness > MAX_LINE_THICKNESS) {
        newThickness = MAX_LINE_THICKNESS;
    }
    glLineWidth(newThickness);
    glPointSize(newThickness);
    thickness = newThickness / (float)height;
    bounds = Vector2D(newAr, 1.0);
}