#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpenGLFunction.h"
#include "libFull.h"

struct shader {

	unsigned int ID;

};

void createVertexShader(unsigned int * shader, const char * vertexShader);

void createFragmentShader(unsigned int * shader, const char * fragmentShader);

void createProgramShader(unsigned int * progam, unsigned int * vertex, unsigned int * fragment);

unsigned int addShader(const char * vertexFile, const char * fragmentFile);
