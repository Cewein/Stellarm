#pragma warning(disable : 4996)
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

void addProgShader(char const * vertexFile, char const * fragmentFile, unsigned int * program)
{
	//make file stream
	FILE * vertex = NULL;
	vertex = fopen(vertexFile, "rb");
	FILE * fragment = NULL;
	fragment = fopen(fragmentFile, "rb");
	
	//Here is were all the shader ID are define
	unsigned int vertexShader;
	unsigned int fragmentShader;

	if (vertex != NULL && fragment != NULL)
	{
		char * vertexFile = freadInArray(vertex);
		char * fragmentFile = freadInArray(fragment);

		//link everything with above function
		createVertexShader(&vertexShader, vertexFile);
		createFragmentShader(&fragmentShader, fragmentFile);
		createProgramShader(program, &vertexShader, &fragmentShader);

		free(vertexFile);
		free(fragmentFile);

		fclose(vertex);
		fclose(fragment);

		//delete shader because the are compile in the program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		return;
	}

	perror("fopen");
	printf("No shader file found!");
	
	return;
}

void const addInt(unsigned int progId, char * name, int value)
{
	glUniform1i(glGetUniformLocation(progId, name), value);
}

void const addFloat(unsigned int progId, char * name, float value)
{
	glUniform1f(glGetUniformLocation(progId, name), value);
}

void const addVec3(unsigned int progId, char * name, vec3 value)
{
	glUniform3fv(glGetUniformLocation(progId, name), 1, value);
}

void const addVec4(unsigned int progId, char * name, vec4 value)
{
	glUniform4fv(glGetUniformLocation(progId, name), 1, value);
}

void const addMat3(unsigned int progId, char * name, mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(progId, name), 1, GL_FALSE, value[0]);
}

void const addMat4(unsigned int progId, char * name, mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(progId, name), 1, GL_FALSE, value[0]);
}

