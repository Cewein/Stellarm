#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include "GLFWFunction.h"
#include "OpenGLFunction.h"
#include "ShaderFunction.h";

const char * vertexShader = "#version 450 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";

const char * yellow = "#version 450 core\n"
	"out vec4 fragcolor;\n"
	"void main()\n"
	"{\n"
		"fragcolor = vec4(1.,1.,0.,1.);\n"
	"}\n";

const char * green = "#version 450 core\n"
"out vec4 fragcolor;\n"
"void main()\n"
"{\n"
"fragcolor = vec4(0.,1.,0.,1.);\n"
"}\n";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//start a pointer on the windows
	GLFWwindow* window = glfwCreateWindow(800, 600, "Stellarm", NULL, NULL);
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
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	float vertices[] = {
		-0.5, -0.5, 0.0, // bottom left
		0.5, -0.5, 0.0, //bottom right
		-0.5, 0.5, 0.0, // top left
		0.5, 0.5, 0.0 // top right
	};
	
	unsigned int indices[] = {
		0,1,2,
		3,2,1
	};

	//---------------------- BUFFER ----------------------//
	//creating buffer
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	//ALWAYS GEN BUFFER OR ARRAY BEFORE USING THEM//
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind the Vertex Array Object (VAO), next the Vertex Buffer (VBO) and last the Element Buffer/Vertex Attribute (EBO)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//---------------------- SHADER ----------------------//
	//creating and compiling a shader
	//Here creating the vertex shader
	unsigned int vrtShdr;
	
	createVertexShader(&vrtShdr, vertexShader);

	//Here creating the fragment shader
	unsigned int frgShdr;
	unsigned int greenShdr;
	
	createFragmentShader(&frgShdr, yellow);
	createFragmentShader(&greenShdr, green);

	//-------------- SHADER PROGRAM CREATION --------------//
	//here linking all shader together
	unsigned int yellowProgram;
	unsigned int greenProgram;
	
	createProgramShader(&yellowProgram, &vrtShdr, &frgShdr);
	createProgramShader(&greenProgram, &vrtShdr, &greenShdr);

	//here deleting the old shader we don't need them anymore
	glDeleteShader(vrtShdr);
	glDeleteShader(frgShdr);
	glDeleteShader(greenShdr);

	//----------------- VERTEX ATTRIBUTE -----------------//
	//telling OpenGL how to use the vertices array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//------------------- RENDER  LOOP -------------------//
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);
		//rendering
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(yellowProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//check and call event
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}