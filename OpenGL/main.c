#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

#include "GLFWFunction.h"
#include "OpenGLFunction.h"
#include "ShaderFunction.h"
#include "glTexture.h"

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

int main()
{ 
	//FILE * logFile = NULL;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//start a pointer on the windows
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Stellarm", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW Window\n");
		glfwTerminate();
		return -1;
	}

	//add OpenGL to the window
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initilize GLAD");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//---------------------- SHAPES ----------------------//
	//this is a cube
	float cube[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	}; 
	
	vec3 cubePos[] = {
	{ 0.0f,  0.0f,  0.0f  },
	{ 2.0f,  5.0f, -15.0f },
	{ -1.5f, -2.2f, -2.5f },
	{ -3.8f, -2.0f, -12.3f},
	{ 2.4f, -0.4f, -3.5f  },
	{ -1.7f,  3.0f, -7.5f },
	{ 1.3f, -2.0f, -2.5f  },
	{ 1.5f,  2.0f, -2.5f  },
	{ 1.5f,  0.2f, -1.5f  },
	{ -1.3f,  1.0f, -1.5f }
	};

	//---------------------- BUFFER ----------------------//
	//creating buffer
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	//ALWAYS GEN BUFFER OR ARRAY BEFORE USING THEM//
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind the Vertex Array Object (VAO), next the Vertex Buffer (VBO) and last the Element Buffer/Vertex Attribute (EBO)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	//enable the z buffer
	glEnable(GL_DEPTH_TEST);

	//-------------- SHADER PROGRAM CREATION --------------//
	//here linking all shader together
	unsigned int shaderProgram;
	
	addProgShader("shader\\vertex.glsl", "shader\\Yellow.glsl", &shaderProgram);

	//----------------- VERTEX ATTRIBUTE -----------------//
	//telling OpenGL how to use the vertices array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//------------------ TEXTURE OPTION ------------------//

	unsigned int wallTexture;
	createTexture(&wallTexture, "texture\\wall.jpg", FALSE);
	unsigned int happyFace;
	createTexture(&happyFace, "texture\\awesomeface.png", TRUE);

	//because we use multiple texture set a number for each texture (cannot be the same)
	glUseProgram(shaderProgram);

	addInt(shaderProgram, "wallTexture", 0);
	addInt(shaderProgram, "happyFace", 1);

	//------------------- RENDER  LOOP -------------------//
	

	vec3 redu = { 0.7f,0.7f,0.7f };
	vec3 axeRota = { .5f, 1.f, 0.f };

	Camera camera = {
		.view = GLM_MAT4_IDENTITY_INIT,
		.pos = { 0.f,0.f,3.f },
		.target = { 0.f, 0.f, 0.f },
		.upAxe = { 0.0f, 1.0f, 0.0f },
		.front = { 0.0f, 0.0f, -1.0 },
		.yaw = -90.f,
		.pitch = 0.f,
		.lastX = (float)SCR_HEIGHT / 2,
		.lastY = (float)SCR_WIDTH / 2,
		.lastFrame = 0.0f,
		.deltaTime = 0.0f
	};

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window, &camera);
		processMouse(window, &camera);

		//rendering
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set multiple texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wallTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, happyFace);

		//use shader program
		glUseProgram(shaderProgram);

		//add number, vector and matrix to shader
		float time = glfwGetTime();
		addFloat(shaderProgram, "time", time);

		camera.deltaTime = time - camera.lastFrame;
		camera.lastFrame = time;

		//create matrix for move the cube, cam and lens setting
		glm_vec3_add(camera.pos, camera.front, camera.target);
		glm_lookat(camera.pos, camera.target, camera.upAxe, camera.view);

		mat4 projection = GLM_MAT4_IDENTITY_INIT;

		glm_perspective(glm_rad(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f, projection);
		

		//send the matrix to the shader
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, camera.view[0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection[0]);

		//draw
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++)
		{
			mat4 trans = GLM_MAT4_IDENTITY_INIT;

			glm_translate(trans, cubePos[i]);
			glm_rotate(trans, glm_rad(10.f * i) * time, axeRota);
			//glm_scale(trans, redu);

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, trans[0]);
			glDrawArrays(GL_TRIANGLES,0, 36);
		}


		//check and call event
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}