#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>

///this struct is a OpenGL cam, it need everything for a camera in openGL in C
typedef struct Cams {
	//time for the cam
	float deltaTime;
	float lastFrame;

	double lastX;
	double lastY;

	float yaw;
	float pitch;

	mat4 view; //this is the view of the window

	vec3 pos; //pos of cam
	vec3 target; // where do the cam look
	vec3 direction;
	vec3 upAxe;
	vec3 front;
} Camera;

void shaderCompilStat(unsigned int shader, char * shaderName);

void programCompliStat(unsigned int program, char * programName);