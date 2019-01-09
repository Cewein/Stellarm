#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>

#include "OpenGLFunction.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera * camera);
void processMouse(GLFWwindow * window, Camera * camera);