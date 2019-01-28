#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

#include "GLFWFunction.h"
#include "OpenGLFunction.h"
#include "ShaderFunction.h"
#include "glTexture.h"
#include "lightGL.h"

#include "astro.h"

#define SCR_WIDTH 1200
#define SCR_HEIGHT 1000

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

int main(void)
{
	struct nk_context *ctx = NULL;
	struct nk_colorf bg;
	struct nk_image img;

	FILE * logFile = NULL;

	Planet * planet = malloc(sizeof(Planet) * 10);

	getPlanetPosition(planet);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//start a pointer on the windows
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Stellarm 1.0 beta release", NULL, NULL);
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

	
	initGUI(&ctx, &img, window);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//---------------------- SHAPES ----------------------//

	/////////////////////// LOADING OBJ /////////////////////// 

	tinyobj_attrib_t attrib;
	tinyobj_shape_t * shapes = NULL;
	int num_shapes;
	tinyobj_material_t * materials = NULL;
	int num_materials;

	int data_len = 0;

	FILE * objFile = NULL;
	objFile = fopen("JUPITER.obj", "rb");

	data_len = fsize(objFile);
	char * data = freadInArray(objFile);
	printf("filesize : %d\n", (int)data_len);
	unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
	int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials, data, data_len, flags);

	float * cubeArray = malloc(sizeof(float) * 8 * attrib.num_faces);

	for (int i = 0; i < attrib.num_faces; i++)
	{
		int v = attrib.faces[i].v_idx;
		int vt = attrib.faces[i].vt_idx;
		int vn = attrib.faces[i].vn_idx;

		cubeArray[i * 8] = attrib.vertices[v * 3 + 0];
		cubeArray[i * 8 + 1] = attrib.vertices[v * 3 + 1];
		cubeArray[i * 8 + 2] = attrib.vertices[v * 3 + 2];
		cubeArray[i * 8 + 3] = attrib.normals[vn * 3 + 0];
		cubeArray[i * 8 + 4] = attrib.normals[vn * 3 + 1];
		cubeArray[i * 8 + 5] = attrib.normals[vn * 3 + 2];
		cubeArray[i * 8 + 6] = attrib.texcoords[vt * 2 + 0];
		cubeArray[i * 8 + 7] = attrib.texcoords[vt * 2 + 1];
	}

	unsigned int sphereVBO;
	unsigned int sphereVAO;

	{
		glGenVertexArrays(1, &sphereVAO);
		glGenBuffers(1, &sphereVBO);

		glBindVertexArray(sphereVAO);

		glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * attrib.num_faces, cubeArray, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	///////////////////////////////////////////////////////////

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
		.lastX = (float)SCR_HEIGHT / 2,
		.lastY = (float)SCR_WIDTH / 2,
		.lastFrame = 0.0f,
		.deltaTime = 0.0f,
		.speed = 2.5f
	};

	Light light = {
		.diffuse = { 0.5f, 0.5f, 0.5f },
		.ambiant = { 0.2f, 0.2f, 0.2f },
		.specular = { 1.f, 1.f, 1.f },
		.position = { 0.0f, 0.0f, 0.0f },
		.watcher = { camera.pos[0],camera.pos[1], camera.pos[2] },

		.constant = 1.f,
		.linear = .00014f,
		.quadratic = .0000007f

	};

	/*bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;*/
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window, &camera);
		processGUI(ctx, &bg,&camera,&light);

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
		glm_perspective(glm_rad(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.f, projection);
		addMat4(shaderProgram, "view", camera.view);
		addMat4(shaderProgram, "projection", projection);

		//draw

		for (int i = 0; i < 10; i++)
		{
			if (!strcmp(planet[i].name, "Lune"))
			{
				createObject(textureArr[i], sphereVAO, attrib.num_faces, shaderProgram, 2.5, planet[i].x * 100 + planet[i-1].x, planet[i].y * 100 + planet[i-1].y, planet[i].z * 100 + planet[i-1 ].z);
			}
			else if (!strcmp(planet[i].name, "Venus"))
			{
				createObject(textureArr[i], sphereVAO, attrib.num_faces, shaderProgram, 10., planet[i].x, planet[i].y, planet[i].z);
				createObject(venusTexture, sphereVAO, attrib.num_faces, shaderProgram, 12.2, planet[i].x, planet[i].y, planet[i].z);
			}
			else if (!strcmp(planet[i].name, "Soleil"))
			{
				glUseProgram(backgroundShader);
				addMat4(backgroundShader, "view", camera.view);
				addMat4(backgroundShader, "projection", projection);

				createObject(textureArr[i], sphereVAO, attrib.num_faces, backgroundShader, 10., 0, 0, 0);
				glUseProgram(shaderProgram);
			}
			else createObject(textureArr[i], sphereVAO, attrib.num_faces, shaderProgram, 10., planet[i].x, planet[i].y, planet[i].z);
		}
		
		glUseProgram(backgroundShader);
		addMat4(backgroundShader, "view", camera.view);
		addMat4(backgroundShader, "projection", projection);

		createObject(background, sphereVAO, attrib.num_faces, backgroundShader, 30000.,0, 0, 0);
		
		/*glUseProgram(lightProgram);
		addMat4(lightProgram, "view", camera.view);
		addMat4(lightProgram, "projection", projection);

		createLum(sphereVAO, attrib.num_faces, lightProgram, light.position);*/

		//check and call event
		nk_glfw3_render(NK_ANTI_ALIASING_OFF);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	tinyobj_attrib_free(&attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	tinyobj_materials_free(materials, num_materials);

	free(cubeArray);

	glDeleteVertexArrays(1, &sphereVAO);
	glDeleteVertexArrays(1, &lightProgram);
	glDeleteBuffers(1, &sphereVBO);

	glfwTerminate();

	return 0;
}