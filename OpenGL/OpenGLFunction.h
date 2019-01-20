#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>

#include "lightGL.h"

/*!
this struct is a OpenGL cam, it need everything for a camera in openGL in C
*/
typedef struct Cams {
	//time for the cam
	float deltaTime;
	float lastFrame;

	//pos of the 2d cam
	double lastX;
	double lastY;

	//angle of the cam
	float yaw; 
	float pitch;

	mat4 view; //this is the view of the window

	//vec of the cam
	vec3 pos; //pos of cam
	vec3 target; // where do the cam look
	vec3 direction;
	vec3 upAxe;
	vec3 front;
} Camera;

void shaderCompilStat(unsigned int shader, char * shaderName);
void programCompliStat(unsigned int program, char * programName);
void calculeView(Camera * camera, float time);

/*!
* @param texture Texture of the object if NULL no texture apply
* @param shape VAO of the object
* @param faceNum number of shape. must be the exacte number
* @param shaderProgram shader ID, see shader creation for more info
*/
void createObject(unsigned int texture, unsigned int shape, int faceNum, unsigned int shaderProgram, float size, float x, float y, float z);

void createLum(unsigned int shape, int faceNum, unsigned int shaderProgram, vec3 lightPos);


