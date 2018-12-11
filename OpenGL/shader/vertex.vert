#version 450 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

uniform float time;

out vec3 vertColor;
out vec2 textCoord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y * cos(time*aPos.x), aPos.z, 1.0);
	vertColor = aColor;
	textCoord = aTextCoord;
}