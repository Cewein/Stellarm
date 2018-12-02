#pragma once
#include <glad/glad.h>

#include "OpenGLFunction.h"

void createVertexShader(unsigned int * shader, const char * vertexShader);

void createFragmentShader(unsigned int * shader, const char * fragmentShader);

void createProgramShader(unsigned int * progam, unsigned int * vertex, unsigned int * fragment);