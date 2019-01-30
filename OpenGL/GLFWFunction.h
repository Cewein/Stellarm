#pragma once
#pragma warning(disable : 4996)

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <cglm/cglm.h>
#include <time.h>

#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

#include "OpenGLFunction.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera * camera);
void processMouse(GLFWwindow * window, Camera * camera);
void processGUI(struct nk_context *ctx, Camera * camera,Light * light);
void initGUI(struct nk_context **ctx, GLFWwindow* window);
GLFWwindow * initWindow(char * winName);