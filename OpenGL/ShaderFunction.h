#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "OpenGLFunction.h"
#include "libFull.h"

void createVertexShader(unsigned int * shader, const char * vertexShader);

void createFragmentShader(unsigned int * shader, const char * fragmentShader);

void createProgramShader(unsigned int * progam, unsigned int * vertex, unsigned int * fragment);

void addProgShader(char const * vertexFile, char const * fragmentFile, unsigned int * program);

void const addInt(unsigned int progId, char * name, int value);
void const addFloat(unsigned int progId, char * name, float value);
void const addVec3(unsigned int progId, char * name, vec3 value);
void const addVec4(unsigned int progId, char * name, vec4 value);
void const addMat3(unsigned int progId, char * name, mat3 value);
void const addMat4(unsigned int progId, char * name, mat4 value);
float getAddTime(unsigned int progId);