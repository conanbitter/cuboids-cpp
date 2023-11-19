#pragma once

#include "glad/gl.h"

typedef GLuint Shader;

Shader compileShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode);