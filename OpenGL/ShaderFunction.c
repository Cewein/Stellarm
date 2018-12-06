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

unsigned int addShader(char const * vertexFile, char const * fragmentFile)
{
	char * buffer = malloc(sizeof(char) * 250);

	FILE * vertex;
	vertex = fopen(vertexFile, "r");
	FILE * fragment;
	fragment = fopen(fragmentFile, "r");

	if (vertex != NULL && fragment != NULL)
	{
		char * vertexShader = malloc(fsize(vertex) + 2 * sizeof(char));
		char * fragmentShader = malloc(fsize(fragment)+ 2 * sizeof(char));

		while (fgets(buffer, 250, vertex) != NULL)
		{
			strcat(vertexShader, buffer);
		}

		while (fgets(buffer, 250, fragment) != NULL)
		{
			strcat(fragmentShader, buffer);
		}

		strcat(vertexShader, "\0");
		strcat(fragmentShader, "\0");

		printf("%s\n%s\n", vertexShader, fragmentShader);


		free(vertexShader);
		free(fragmentShader);
		free(buffer);	

		fclose(vertex);
		fclose(fragment);

		return 1;
	}
	
	free(buffer);

	perror("fopen");
	printf("No shader file found!");
	
	return 0;
}