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

	/////////////////////// LOADING OBJ /////////////////////// 

	tinyobj_attrib_t attrib;
	tinyobj_shape_t * shapes = NULL;
	int num_shapes;
	tinyobj_material_t * materials = NULL;
	int num_materials;

	int data_len = 0;

	FILE * objFile = NULL;
	objFile = fopen("cube.obj", "rb");

	data_len = fsize(objFile);
	char * data = freadInArray(objFile);
	printf("filesize : %d\n", (int)data_len);
	unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
	int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials, data, data_len, flags);

	printf("# of shapes     = %d\n", (int)num_shapes);
	printf("# of materials  = %d\n", (int)num_materials);
	printf("# of vertices   = %d\n", (int)attrib.num_vertices);
	printf("# of face       = %d\n", (int)attrib.num_faces);
	//printf("name diffure    = %s\n", materials->diffuse_texname);
	printf("sizeof vertices = %d\n", sizeof(float) * attrib.num_vertices);
	printf("sizeof cube arr = %d\n", sizeof(cube));

	for (int i = 0; i < attrib.num_face_num_verts; i++) printf("indice %d : %f\n", i, attrib.material_ids[i]);


	///////////////////////////////////////////////////////////

	unsigned int jupElm;
	unsigned int jupVBO;
	unsigned int jupVAO;

	{
		glGenVertexArrays(1, &jupVAO);
		glGenBuffers(1, &jupVBO);
		glGenBuffers(1, &jupElm);

		glBindVertexArray(jupVAO);

		glBindBuffer(GL_ARRAY_BUFFER, jupVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * attrib.num_vertices, attrib.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, jupElm);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, attrib.);

	}


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
	unsigned int jupProg;
	
	addProgShader("shader\\vertex.glsl", "shader\\texture.glsl", &shaderProgram);
	addProgShader("shader\\vertexNotexture.glsl", "shader\\lightFrag.glsl", &lightProgram);
	addProgShader("shader\\vertexNotexture.glsl", "shader\\lightFrag.glsl", &jupProg);


	//------------------ TEXTURE OPTION ------------------//

	unsigned int boxTexture;
	unsigned int boxSpecular;
	unsigned int boxEmissive;

	createTexture(&boxTexture, "texture\\container2.png", FALSE);
	createTexture(&boxSpecular, "texture\\container2_specular.png", FALSE);
	createTexture(&boxEmissive, "texture\\matrix.jpg", FALSE);

	//because we use multiple texture set a number for each texture (cannot be the same)
	glUseProgram(shaderProgram);

	addInt(shaderProgram, "material.diffuse", 0);
	addInt(shaderProgram, "material.specular", 1);
	addInt(shaderProgram, "material.emissive", 2);

	//------------------- RENDER  LOOP -------------------//
	

	vec3 redu = { 0.2f,0.2f,0.2f };
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

	Light light = {
		.diffuse = { 0.5f, 0.5f, 0.5f },
		.ambiant = { 0.2f, 0.2f, 0.2f },
		.specular = { 1.f, 1.f, 1.f },
		.direction = { -0.2f, -1.0f, -0.3f},
		.position = { 0.0f, 1.0f, 5.0f },
		.watcher = { camera.pos[0],camera.pos[2], camera.pos[2] },

		.constant = 1.0f,
		.linear = .09f,
		.quadratic = 0.0032f

	};

	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window, &camera);
		processMouse(window, &camera);

		//rendering
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set multiple texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, boxTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, boxSpecular);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, boxEmissive);

		//use shader program
		glUseProgram(shaderProgram);

		//add number, vector and matrix to shader
		float time = glfwGetTime();
		addFloat(shaderProgram, "time", time);

		sendLightInfo(light, shaderProgram);
		addFloat(shaderProgram, "material.shininess", 32.0f);

		camera.deltaTime = time - camera.lastFrame;
		camera.lastFrame = time;

		//create matrix for move the cube, cam and lens setting
		glm_vec3_add(camera.pos, camera.front, camera.target);
		glm_lookat(camera.pos, camera.target, camera.upAxe, camera.view);

		mat4 projection = GLM_MAT4_IDENTITY_INIT;
		//make the cam
		glm_perspective(glm_rad(45.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f, projection);
		//send the matrix to the shader
		addMat4(shaderProgram, "view", camera.view);
		addMat4(shaderProgram, "projection", projection);

		//draw
		glBindVertexArray(cubeVAO);
		for (int i = 0; i < 10; i++)
		{
			mat4 trans = GLM_MAT4_IDENTITY_INIT;

			glm_translate(trans, cubePos[i]);
			glm_rotate(trans, glm_rad(10.f * i) * time, axeRota);
			//glm_scale(trans, redu);

			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, trans[0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glUseProgram(lightProgram);
		glBindVertexArray(lightVAO);
		mat4 lightPosRedu = GLM_MAT4_IDENTITY_INIT;

		glm_translate(lightPosRedu, light.position);
		glm_scale(lightPosRedu, redu);

		addMat4(lightProgram, "view", camera.view);
		addMat4(lightProgram, "projection", projection);
		addMat4(lightProgram, "transform", lightPosRedu);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//check and call event
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	tinyobj_attrib_free(&attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	tinyobj_materials_free(materials, num_materials);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightProgram);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}