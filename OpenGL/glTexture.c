#include "glTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void createTexture(unsigned int * id, char * pathTexture, int flipOnLoad) 
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nbChannels;
	stbi_set_flip_vertically_on_load(flipOnLoad);
	unsigned char *data = stbi_load(pathTexture, &width, &height, &nbChannels, 0);
	if (data)
	{
		//printf("nb channel : %d", nbChannels);

		switch (nbChannels)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Texture from %s : Data not loaded", pathTexture);
	}

}
