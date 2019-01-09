#include "lightGL.h"

void sendLightInfo(Light light, unsigned int shader)
{
	addVec3(shader, "light.diffuse", light.diffuse);
	addVec3(shader, "light.ambient", light.ambiant);
	addVec3(shader, "light.specular", light.specular);
	addVec3(shader, "light.direction", light.direction);
	addVec3(shader, "light.position", light.position);
	addVec3(shader, "viewPos", light.watcher);
	addFloat(shader, "light.constant", light.constant);
	addFloat(shader, "light.linear", light.linear);
	addFloat(shader, "light.quadratic", light.quadratic);
}
