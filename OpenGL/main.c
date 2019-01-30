#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

#include "GLFWFunction.h"
#include "OpenGLFunction.h"
#include "ShaderFunction.h"
#include "glTexture.h"
#include "lightGL.h"

#include "astro.h"

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

int main(void)
{
	struct nk_context *ctx = NULL;
	struct nk_colorf bg;

	//FILE * logFile = NULL;

	Planet * planet = malloc(sizeof(Planet) * 10);
	getPlanetPosition(planet);

	//start a pointer on the windows
	GLFWwindow * window = initWindow("Stellarm pre-release 1.0");
	initGUI(&ctx, window);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//---------------------- SHAPES ----------------------//

	unsigned int sphereVBO;
	unsigned int sphereVAO;
	int objNbOfFaces;
	float * objArray = loadObj("JUPITER.obj", &objNbOfFaces);
	glBindObj(objArray, objNbOfFaces, &sphereVBO, &sphereVAO);

	unsigned int flippedVBO;
	unsigned int flippedVAO;
	int flippedFaces;
	float * flippedArray = loadObj("flippedSphere.obj", &flippedFaces);
	glBindObj(flippedArray, flippedFaces, &flippedVBO, &flippedVAO);

	//enable the z buffer
	glEnable(GL_DEPTH_TEST);

	//-------------- SHADER PROGRAM CREATION --------------//
	//here linking all shader together
	unsigned int shaderProgram;
	unsigned int lightProgram;
	unsigned int backgroundShader;
	
	addProgShader("shader\\vertex.glsl", "shader\\texture.glsl", &shaderProgram);
	addProgShader("shader\\vertexNotexture.glsl", "shader\\lightFrag.glsl", &lightProgram);
	addProgShader("shader\\vertex.glsl", "shader\\textureNoLight.glsl", &backgroundShader);


	//------------------ TEXTURE OPTION ------------------//


	unsigned int jupiterTexture;
	unsigned int marsTexture;
	unsigned int mercureTexture;
	unsigned int venusTexture;
	unsigned int earthTexture;
	unsigned int sunTexture;
	unsigned int background;
	unsigned int moonTexture;
	unsigned int saturneTexture;
	unsigned int uranusTexture;
	unsigned int neptuneTexture;

	unsigned int textureArr[10];

	createTexture(&textureArr[0],"texture\\sun.jpg", TRUE);
	createTexture(&textureArr[1],"texture\\earth.jpg", TRUE);
	createTexture(&textureArr[2],"texture\\moon.jpg", TRUE);
	createTexture(&textureArr[3],"texture\\mercury.jpg", TRUE);
	createTexture(&textureArr[4],"texture\\venus.jpg", TRUE);
	createTexture(&textureArr[5],"texture\\mars.jpg", TRUE);
	createTexture(&textureArr[6],"texture\\jupiter.png", TRUE);
	createTexture(&textureArr[7],"texture\\saturn.jpg", TRUE);
	createTexture(&textureArr[8],"texture\\uranus.jpg", TRUE);
	createTexture(&textureArr[9],"texture\\neptune.jpg", TRUE);
	
	createTexture(&venusTexture, "texture\\venus_atmosphere.jpg", TRUE);
	createTexture(&background, "texture\\starmap.jpg", FALSE);

	//because we use multiple texture set a number for each texture (cannot be the same)
	glUseProgram(shaderProgram);

	addInt(shaderProgram, "material.diffuse", 0);
	addInt(shaderProgram, "material.specular", 1);

	//------------------- RENDER  LOOP -------------------//
	

	vec3 redu = { 0.2f,0.2f,0.2f };
	vec3 axeRota = { .5f, 1.f, 0.f };
	vec3 zero = GLM_VEC3_ZERO_INIT;

	Camera camera = {
		.view = GLM_MAT4_IDENTITY_INIT,
		.pos = { 0.f,5.f,10.f },
		.target = { 0.f, 0.f, 0.f },
		.upAxe = { 0.0f, 1.0f, 0.0f },
		.front = { 0.0f, 0.0f, -1.0 },
		.yaw = -90.f,
		.pitch = -45.f,
		.FOV = 45.f,
		.lastX = (float)SCR_HEIGHT / 2,
		.lastY = (float)SCR_WIDTH / 2,
		.lastFrame = 0.0f,
		.deltaTime = 0.0f,
		.speed = 2.5f
	};

	Light light = {
		.diffuse = { 0.5f, 0.5f, 0.5f },
		.ambiant = { 0.02f, 0.02f, 0.02f },
		.specular = { 1.f, 1.f, 1.f },
		.position = { 0.0f, 0.0f, 0.0f },
		.watcher = { camera.pos[0],camera.pos[1], camera.pos[2] },

		.constant = 1.f,
		.linear = .000004f,
		.quadratic = .000000000f

	};

	/*bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;*/
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window, &camera);
		processGUI(ctx, &camera, &light);

		glEnable(GL_DEPTH_TEST); //this allow the graphic pipeline to work

		//rendering
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use shader program
		glUseProgram(shaderProgram);

		//add number, vector and matrix to shader
		float time = glfwGetTime();
		addFloat(shaderProgram, "time", time);

		sendLightInfo(light, shaderProgram);
		addFloat(shaderProgram, "material.shininess", 32.0f); 
		calculeView(&camera, time);

		mat4 projection = GLM_MAT4_IDENTITY_INIT;
		glm_perspective(glm_rad(camera.FOV), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.f, projection);
		addMat4(shaderProgram, "view", camera.view);
		addMat4(shaderProgram, "projection", projection);

		//draw

		for (int i = 0; i < 10; i++)
		{
			if (!strcmp(planet[i].name, "Lune"))
			{
				createObject(textureArr[i], sphereVAO, objNbOfFaces, shaderProgram, getSize(i), planet[i].x * 100 + planet[i-1].x, planet[i].y * 100 + planet[i-1].y, planet[i].z * 100 + planet[i-1 ].z);
			}
			else if (!strcmp(planet[i].name, "Venus"))
			{
				createObject(textureArr[i], sphereVAO, objNbOfFaces, shaderProgram, getSize(i), planet[i].x, planet[i].y, planet[i].z);
				createObject(venusTexture, flippedVAO, objNbOfFaces, shaderProgram, 1.2, planet[i].x, planet[i].y, planet[i].z);
			}
			else if (!strcmp(planet[i].name, "Soleil"))
			{
				glUseProgram(backgroundShader);
				addMat4(backgroundShader, "view", camera.view);
				addMat4(backgroundShader, "projection", projection);

				createObject(textureArr[i], sphereVAO, objNbOfFaces, backgroundShader, getSize(i)/4, 0, 0, 0);
				glUseProgram(shaderProgram);
			}
			else createObject(textureArr[i], sphereVAO, objNbOfFaces, shaderProgram, getSize(i), planet[i].x, planet[i].y, planet[i].z);
		}
		
		glUseProgram(backgroundShader);
		addMat4(backgroundShader, "view", camera.view);
		addMat4(backgroundShader, "projection", projection);

		createObject(background, sphereVAO, objNbOfFaces, backgroundShader, 30000.,0, 0, 0);

		//check and call event
		nk_glfw3_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	free(objArray);

	glDeleteVertexArrays(1, &sphereVAO);
	glDeleteVertexArrays(1, &lightProgram);
	glDeleteBuffers(1, &sphereVBO);
	nk_glfw3_shutdown();
	glfwTerminate();

	return 0;
}