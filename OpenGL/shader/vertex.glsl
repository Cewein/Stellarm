#version 450 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform float time;
uniform mat4 transform; //this move the object
uniform mat4 view; //this is the camera
uniform mat4 projection; // this set the lens of the camera

out vec3 pos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 fragPos;

void main()
{
	//read for right to left
	gl_Position =  projection * view * transform * vec4(aPos, 1.0);
	Normal = mat3(transpose(inverse(transform))) * aNormal;
	TexCoord = aTexCoord;
	fragPos = vec3(transform * vec4(aPos, 1.0));
	pos = aPos;
	
}