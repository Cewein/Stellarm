#pragma once

#include <cglm/cglm.h>
#include "ShaderFunction.h"

/*!
This create a light object that can be move everywhere
*/
typedef struct Lights{
	vec3 diffuse;
	vec3 ambiant;
	vec3 specular;
	vec3 direction;
	vec3 position;

	vec3 watcher; //this is the posiion of the camera

	float constant;
	float linear;
	float quadratic;

}Light;


void sendLightInfo(Light light, unsigned int shader);