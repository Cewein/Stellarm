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

#define SCR_WIDTH 1200
#define SCR_HEIGHT 1000

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

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	//---------------------- SHAPES ----------------------//
	//this is a cube
	float cube[] = {
		// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

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

	unsigned int shpereVBO;
	unsigned int shpereVAO;

	{
		glGenVertexArrays(1, &shpereVAO);
		glGenBuffers(1, &shpereVBO);

		glBindVertexArray(shpereVAO);

		glBindBuffer(GL_ARRAY_BUFFER, shpereVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * attrib.num_faces, cubeArray, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	///////////////////////////////////////////////////////////


	//---------------------- BUFFER ----------------------//
	//creating buffer
	unsigned int VBO;
	unsigned int cubeVAO;

	{
		//ALWAYS GEN BUFFER OR ARRAY BEFORE USING THEM//
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		//bind the Vertex Array Object (VAO), next the Vertex Buffer (VBO) and last the Element Buffer/Vertex Attribute (EBO)
		glBindVertexArray(cubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

		//box vertex attribute
		//telling OpenGL how to use the vertices array
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	//light buffer
	unsigned int lightVAO;

	{
		glGenVertexArrays(1, &lightVAO);

		glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

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


	unsigned int planetTexture;
	unsigned int background;

	//materials->diffuse_texname = removeEnter(materials->diffuse_texname);
	createTexture(&planetTexture, "texture\\jupiter.png", TRUE);
	createTexture(&background, "texture\\starmap.jpg", FALSE);

	//because we use multiple texture set a number for each texture (cannot be the same)
	glUseProgram(shaderProgram);

	addInt(shaderProgram, "material.diffuse", 0);
	addInt(shaderProgram, "material.specular", 1);

	//glUseProgram(jupProg);
	//------------------- RENDER  LOOP -------------------//
	

	vec3 redu = { 0.2f,0.2f,0.2f };
	vec3 axeRota = { .5f, 1.f, 0.f };
	vec3 zero = GLM_VEC3_ZERO_INIT;

	Camera camera = {
		.view = GLM_MAT4_IDENTITY_INIT,
		.pos = { 0.f,2.f,3.f },
		.target = { 0.f, 0.f, 0.f },
		.upAxe = { 0.0f, 1.0f, 0.0f },
		.front = { 0.0f, 0.0f, -1.0 },
		.yaw = -90.f,
		.pitch = -45.f,
		.lastX = (float)SCR_HEIGHT / 2,
		.lastY = (float)SCR_WIDTH / 2,
		.lastFrame = 0.0f,
		.deltaTime = 0.0f
	};

	Light light = {
		.diffuse = { 0.5f, 0.5f, 0.5f },
		.ambiant = { 0.2f, 0.2f, 0.2f },
		.specular = { 1.f, 1.f, 1.f },
		.direction = { -0.2f, -1.0f, -0.3f},
		.position = { 0.0f, 0.0f, -20.0f },
		.watcher = { camera.pos[0],camera.pos[2], camera.pos[2] },

		.constant = .01f,
		.linear = .09f,
		.quadratic = 0.00032f

	};

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window, &camera);
		processMouse(window, &camera);

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
		glm_perspective(glm_rad(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.f, projection);
		addMat4(shaderProgram, "view", camera.view);
		addMat4(shaderProgram, "projection", projection);

		//draw

		createObject(planetTexture, shpereVAO, attrib.num_faces, shaderProgram, 1., 0. ,0. ,0.);

		glUseProgram(backgroundShader);
		addMat4(backgroundShader, "view", camera.view);
		addMat4(backgroundShader, "projection", projection);

		createObject(background, shpereVAO, attrib.num_faces, backgroundShader, 3000.,0.,0.,0.);
		
		glUseProgram(lightProgram);
		addMat4(lightProgram, "view", camera.view);
		addMat4(lightProgram, "projection", projection);

		createLum(lightVAO, 36, lightProgram, light.position);

		//check and call event
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	tinyobj_attrib_free(&attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	tinyobj_materials_free(materials, num_materials);

	free(cubeArray);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightProgram);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}