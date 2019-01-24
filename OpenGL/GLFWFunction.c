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
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camSpeed *= 10;
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
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		processMouse(window, camera);
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

void processGUI(struct nk_context *ctx, struct nk_colorf * bg, Camera * camera, Light * light)
{
	nk_glfw3_new_frame();
	if (nk_begin(ctx, "Param", nk_rect(5, 5, 250, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		float ratio[] = { 220, 150 };
		nk_layout_row(ctx, NK_STATIC, 30, 1, ratio);
		nk_label(ctx, "Speed option", NK_TEXT_ALIGN_CENTERED);
		nk_property_float(ctx, "Speed:", 0., &camera->speed, 50., 0.01, 0.1);
		nk_label(ctx, "Light option", NK_TEXT_ALIGN_CENTERED);
		nk_property_float(ctx, "constant:", -1., &light->constant, 2.0, 0.001, 0.001);
		nk_labelf(ctx, NK_TEXT_ALIGN_CENTERED, "value: %f", light->constant);
		nk_property_float(ctx, "linear:", -1., &light->linear, 2.0, 0.00001, 0.00001);
		nk_labelf(ctx, NK_TEXT_ALIGN_CENTERED, "value: %f", light->linear);
		nk_property_float(ctx, "quadratic:", -1., &light->quadratic, 2.0, 0.000001, 0.000001);
		nk_labelf(ctx, NK_TEXT_ALIGN_CENTERED, "value: %f", light->quadratic);
	}
	nk_end(ctx);

	if (nk_begin(ctx, "Time", nk_rect(500, 5, 250, 300), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{
		time_t curtime;
		struct tm * timeStr;
		time(&curtime);
		timeStr = gmtime(&curtime);
		float ratio[] = { 220, 150 };
		nk_layout_row(ctx, NK_STATIC, 30, 1, ratio);
		nk_label(ctx, "Select date", NK_TEXT_ALIGN_CENTERED);
		int year = timeStr->tm_year + 1900;
		nk_property_int(ctx, "Year:", 1900, &year, INFINITE, 1, 1);
		timeStr->tm_year = year - 1900;
		int month = timeStr->tm_mon + 1;
		nk_property_int(ctx, "Month:", 1, &month, 12, 1, 1);
		timeStr->tm_mon = month - 1;
		nk_property_int(ctx, "Day:", 1, &timeStr->tm_mday, 31, 1, 1);
		nk_property_int(ctx, "Hour:", 0, &timeStr->tm_hour, 23, 1, 1);
		nk_property_int(ctx, "Minute:", 0, &timeStr->tm_min, 59, 1, 1);
		nk_property_int(ctx, "Second:", 0, &timeStr->tm_sec, 59, 1, 1);

		if (nk_button_label(ctx, "Done"));
	}
	nk_end(ctx);
}	
