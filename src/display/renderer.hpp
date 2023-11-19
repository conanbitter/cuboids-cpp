#pragma once
#include <vector>
#include "../vectors.hpp"
#include "shaders.hpp"
#include <glad/gl.h>

enum class RendererState { Ready,
                           NotReady,
                           DrawingLines,
                           DrawingPoints };

enum class RenderType { Lines,
                        Points };

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#pragma pack(push, 1)
struct Vertex {
    Vector2D pos;
    Color color;
};
#pragma pack(pop)

class Renderer {
   public:
    Vector2D getBounds() { return bounds; }
    float getThickness() { return thickness; }
    void startRender();
    void beginDraw(RenderType renderType);
    void addPoint(Vector2D pos, Color color);
    void newLine() { isNewLine = true; }
    void endDraw();
    void finishRender();
    void setViewport(int width, int height);

   private:
    Renderer() : state{RendererState::NotReady} {}
    void free();
    void init();

    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLint arLocation;
    RendererState state;
    std::vector<Vertex> vertices;
    bool isNewLine;
    float thickness;
    Vector2D bounds;

    friend class AppWindow;
};