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

void calculeView(Camera * camera, float time)
{
	camera->deltaTime = time - camera->lastFrame;
	camera->lastFrame = time;

	glm_vec3_add(camera->pos, camera->front, camera->target);
	glm_lookat(camera->pos, camera->target, camera->upAxe, camera->view);
}

void createObject(unsigned int texture, unsigned int shape, int faceNum, unsigned int shaderProgram, float size, float x, float y, float z)
{
	if (texture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glBindVertexArray(shape);

	mat4 objTrans = GLM_MAT4_IDENTITY_INIT;

	vec3 objScale = { size, size, size};
	vec3 objPos = { x, y, z };
	glm_translate(objTrans, objPos);
	glm_scale(objTrans, objScale);

	addMat4(shaderProgram, "transform", objTrans);

	glDrawArrays(GL_TRIANGLES, 0, faceNum);
}

void createLum(unsigned int shape, int faceNum, unsigned int shaderProgram, vec3 lightPos)
{
	glBindVertexArray(shape);

	mat4 lightTrans = GLM_MAT4_IDENTITY_INIT;
	glm_translate(lightTrans, lightPos);
	addMat4(shaderProgram, "transform", lightTrans);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, faceNum);
}