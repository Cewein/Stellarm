#pragma once
#pragma warning(disable : 4996)

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>
#include <time.h>

#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

#include "OpenGLFunction.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera * camera);
void processMouse(GLFWwindow * window, Camera * camera);
void processGUI(struct nk_context *ctx, struct nk_colorf * bg,Camera * camera,Light * light);
void initGUI(struct nk_context **ctx, struct nk_image * img, GLFWwindow* window);