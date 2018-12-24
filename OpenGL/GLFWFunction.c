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

void processMouse(GLFWwindow * window, Camera * camera)
{
	double xpos;
	double ypos;

	glfwGetCursorPos(window, &xpos, &ypos);

	if (xpos != camera->lastX || ypos != camera->lastY)
	{
		float xoffset = xpos - camera->lastX;
		float yoffset = camera->lastY - ypos;

		float sensivity = 0.1f;

		xoffset *= sensivity;
		yoffset *= sensivity;

		camera->yaw += xoffset;
		camera->pitch += yoffset;
		if (camera->pitch > 89.0f) camera->pitch = 89.f;
		if (camera->pitch < -89.0f) camera->pitch = -89.f;

		vec3 front;
		front[0] = cos(glm_rad(camera->pitch)) * cos(glm_rad(camera->yaw));
		front[1] = sin(glm_rad(camera->pitch));
		front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
		glm_normalize_to(front, camera->front);

		camera->lastX = xpos;
		camera->lastY = ypos;
	}
}

