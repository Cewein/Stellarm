#include "GLFWFunction.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera * camera)
{
	float camSpeed = 2.5f  * camera->deltaTime;
	vec3 tmp = GLM_VEC3_ZERO_INIT;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		glm_vec3_muladds(camera->front, camSpeed, camera->pos);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm_vec3_muladds(camera->front, camSpeed, tmp);
		glm_vec3_sub(camera->pos, tmp, camera->pos);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm_cross(camera->front, camera->upAxe, tmp);
		glm_normalize(tmp);
		glm_vec3_negate(tmp);
		glm_vec3_muladds(tmp, camSpeed, camera->pos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm_cross(camera->front, camera->upAxe, tmp);
		glm_normalize(tmp);
		glm_vec3_muladds(tmp, camSpeed, camera->pos);
	}
}


