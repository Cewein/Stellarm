#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <cglm/cglm.h>

typedef struct Cams {
	vec3 eye;
} Camera;

void shaderCompilStat(unsigned int shader, char * shaderName);

void programCompliStat(unsigned int program, char * programName);