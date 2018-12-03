#include "OpenGLFunction.h"

void shaderCompilStat(unsigned int shader, char * shaderName)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", shaderName, infoLog);
		printf("------------ END OF ERROR ----------------\n");
	}
}

void programCompliStat(unsigned int program, char * programName)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", programName, infoLog);
		printf("------------ END OF ERROR ----------------\n");
	}

}
