#version 450

layout (location = 0) in vec3 aPos; 

uniform mat4 transform; //this move the object
uniform mat4 view; //this is the camera
uniform mat4 projection; // this set the lens of the camera


void main()
{
	gl_Position =  projection * view * transform * vec4(aPos, 1.0);
}