#include "ShaderFunction.h"

void createVertexShader(unsigned int * shader, const char * vertexShader)
{
	*shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*shader, 1, &vertexShader, NULL);
	glCompileShader(*shader);

	shaderCompilStat(*shader, "VERTEX SHADER");
}

void createFragmentShader(unsigned int * shader, const char * fragmentShader)
{
	*shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*shader, 1, &fragmentShader, NULL);
	glCompileShader(*shader);

	shaderCompilStat(*shader, "FRAGMENT SHADER");
}

void createProgramShader(unsigned int * program, unsigned int * vertex, unsigned int * fragment)
{
	*program = glCreateProgram();
	glAttachShader(*program, *vertex);
	glAttachShader(*program, *fragment);
	glLinkProgram(*program);

	programCompliStat(*program, "SHADER LINK PROGRAM");
}

