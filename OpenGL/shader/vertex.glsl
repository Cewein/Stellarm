#version 450 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

uniform float time;
uniform mat4 transform; //this move the object
uniform mat4 view; //this is the camera
uniform mat4 projection; // this set the lens of the camera

out vec3 pos;
out vec3 vertColor;
out vec2 textCoord;

void main()
{
	//read for right to left
	gl_Position =  projection * view * transform * vec4(aPos, 1.0);
	vertColor = aColor;
	textCoord = aTextCoord;
	pos = aPos;
}