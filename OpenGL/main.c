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

	printf("# of shapes    = %d\n", (int)num_shapes);
	printf("# of materials = %d\n", (int)num_materials);
	printf("# name diffure = %s\n", materials->diffuse_texname);

	tinyobj_attrib_free(&attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	tinyobj_materials_free(materials, num_materials);

	//---------------------- BUFFER ----------------------//
	//creating buffer
	unsigned int VBO;
	unsigned int cubeVAO;
	unsigned int EBO;

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

	//light buffer
	unsigned int lightVAO;

	glGenVertexArrays(1,&lightVAO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//enable the z buffer
	glEnable(GL_DEPTH_TEST);

	//-------------- SHADER PROGRAM CREATION --------------//
	//here linking all shader together
	unsigned int shaderProgram;
	unsigned int lightProgram;
	
	addProgShader("shader\\vertex.glsl", "shader\\texture.glsl", &shaderProgram);
	addProgShader("shader\\vertexNotexture.glsl", "shader\\lightFrag.glsl", &lightProgram);

	//------------------ TEXTURE OPTION ------------------//

	unsigned int boxTexture;
	createTexture(&boxTexture, "texture\\container2.png", FALSE);
	unsigned int boxSpecular;
	createTexture(&boxSpecular, "texture\\container2_specular.png", FALSE);
	unsigned int boxEmissive;
	createTexture(&boxEmissive, "texture\\matrix.jpg", FALSE);

	//because we use multiple texture set a number for each texture (cannot be the same)
	glUseProgram(shaderProgram);

	addInt(shaderProgram, "material.diffuse", 0);
	addInt(shaderProgram, "material.specular", 1);
	addInt(shaderProgram, "material.emissive", 2);

	//------------------- RENDER  LOOP -------------------//
	

	vec3 redu = { 0.2f,0.2f,0.2f };
	vec3 axeRota = { .5f, 1.f, 0.f };
	vec3 lightPos = { 1.2f, 1.0f, 2.0f };

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

		vec3 lightColor = { 1.0,1.0,1.0 };

		//light struct
		vec3 ldiffuse = { 0.5f, 0.5f, 0.5f };
		//glm_vec3_mul(ldiffuse, lightColor, ldiffuse);
		addVec3(shaderProgram, "light.diffuse", ldiffuse);
		vec3 lambiant = { 0.2f, 0.2f, 0.2f };
		//glm_vec3_mul(lambiant, ldiffuse, lambiant);
		addVec3(shaderProgram, "light.ambient", lambiant);
		vec3 lspecular = { 1.f, 1.f, 1.f };
		addVec3(shaderProgram, "light.specular", lspecular);
		vec3 ldirection = { -0.2f, -1.0f, -0.3f };
		addVec3(shaderProgram, "light.direction", ldirection);
		addVec3(shaderProgram, "light.position", lightPos);
		addVec3(shaderProgram, "viewPos", camera.pos);
		addFloat(shaderProgram, "light.constant", 1.0f);
		addFloat(shaderProgram, "light.linear", .09f);
		addFloat(shaderProgram, "light.quadratic", 0.0032f);
		
		//material struct
		addFloat(shaderProgram, "material.shininess", 32.0f);


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
		addVec3(shaderProgram, "Color", lightColor);
		glBindVertexArray(lightVAO);
		mat4 lightPosRedu = GLM_MAT4_IDENTITY_INIT;
		lightPos[2] = sin(time) * 2;
		lightPos[0] = cos(time) * 4;
		glm_translate(lightPosRedu, lightPos);
		glm_scale(lightPosRedu, redu);

		addMat4(lightProgram, "view", camera.view);
		addMat4(lightProgram, "projection", projection);
		addMat4(lightProgram, "transform", lightPosRedu);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//check and call event
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightProgram);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}