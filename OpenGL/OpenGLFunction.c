#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "OpenGLFunction.h"

void shaderCompilStat(unsigned int shader, char * shaderName)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", shaderName, infoLog);
		printf("------------ END OF ERROR ----------------\n");
	}
}

void programCompliStat(unsigned int program, char * programName)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("ERROR [%s] DID NOT COMPILE!\n%s\n", programName, infoLog);
		printf("------------ END OF ERROR ----------------\n");
	}

}

void calculeView(Camera * camera, float time)
{
	camera->deltaTime = time - camera->lastFrame;
	camera->lastFrame = time;

	glm_vec3_add(camera->pos, camera->front, camera->target);
	glm_lookat(camera->pos, camera->target, camera->upAxe, camera->view);
}

void createObject(unsigned int texture, unsigned int shape, int faceNum, unsigned int shaderProgram, float size, float x, float y, float z)
{
	glUseProgram(shaderProgram);

	if (texture != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glBindVertexArray(shape);

	mat4 objTrans = GLM_MAT4_IDENTITY_INIT;

	vec3 objScale = { size, size, size};
	vec3 objPos = { x, y, z };
	glm_translate(objTrans, objPos);
	glm_scale(objTrans, objScale);

	addMat4(shaderProgram, "transform", objTrans);

	glDrawArrays(GL_TRIANGLES, 0, faceNum);
}

void createLum(unsigned int shape, int faceNum, unsigned int shaderProgram, vec3 lightPos)
{
	glBindVertexArray(shape);

	mat4 lightTrans = GLM_MAT4_IDENTITY_INIT;
	glm_translate(lightTrans, lightPos);
	addMat4(shaderProgram, "transform", lightTrans);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, faceNum);
}

float * loadObj(char * file, int * nbOfFaces)
{
	tinyobj_attrib_t attrib;
	tinyobj_shape_t * shapes = NULL;
	int num_shapes;
	tinyobj_material_t * materials = NULL;
	int num_materials;

	{
		int data_len = 0;

		FILE * objFile = NULL;
		objFile = fopen(file, "rb");

		data_len = fsize(objFile);
		char * data = freadInArray(objFile);
		//printf("filesize : %d\n", (int)data_len);
		unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
		int ret = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, &num_materials, data, data_len, flags);
	}

	float * objArray = malloc(sizeof(float) * 8 * attrib.num_faces);
	{
		for (int i = 0; i < attrib.num_faces; i++)
		{
			int v = attrib.faces[i].v_idx;
			int vt = attrib.faces[i].vt_idx;
			int vn = attrib.faces[i].vn_idx;

			objArray[i * 8] = attrib.vertices[v * 3 + 0];
			objArray[i * 8 + 1] = attrib.vertices[v * 3 + 1];
			objArray[i * 8 + 2] = attrib.vertices[v * 3 + 2];
			objArray[i * 8 + 3] = attrib.normals[vn * 3 + 0];
			objArray[i * 8 + 4] = attrib.normals[vn * 3 + 1];
			objArray[i * 8 + 5] = attrib.normals[vn * 3 + 2];
			objArray[i * 8 + 6] = attrib.texcoords[vt * 2 + 0];
			objArray[i * 8 + 7] = attrib.texcoords[vt * 2 + 1];
		}
	}

	*nbOfFaces = attrib.num_faces;

	tinyobj_attrib_free(&attrib);
	tinyobj_shapes_free(shapes, num_shapes);
	tinyobj_materials_free(materials, num_materials);

	return objArray;
}

void glBindObj(float * objArray, int objNbOfFaces, unsigned int * VBO, unsigned int * VAO)
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * objNbOfFaces, objArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}