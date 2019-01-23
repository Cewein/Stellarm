#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#define NK_IMPLEMENTATION
#include "GLFWFunction.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera * camera)
{
	float camSpeed = camera->speed * camera->deltaTime;
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

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void processGUI(struct nk_context *ctx, struct nk_colorf * bg,Camera * camera)
{
	nk_glfw3_new_frame();
	if (nk_begin(ctx, "Param", nk_rect(5, 5, 200, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
		{
			nk_layout_row_push(ctx, 50);
			nk_label(ctx, "Speed:", 110);
			nk_layout_row_push(ctx, 110);
			nk_slider_float(ctx, 0, &camera->speed, 500.0f, 0.1);
		}
	}
	nk_end(ctx);
}

void initGUI(struct nk_context **ctx, struct nk_image * img, GLFWwindow* window)
{
	/////////// setting up Nuklear ///////////
	*ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
	{
		struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		nk_glfw3_font_stash_end();
	}

	{
		int tex_index = 0;
		enum { tex_width = 256, tex_height = 256 };
		char pixels[tex_width * tex_height * 4];
		memset(pixels, 128, sizeof(pixels));
		tex_index = nk_glfw3_create_texture(pixels, tex_width, tex_height);
		*img = nk_image_id(tex_index);
	}
}

