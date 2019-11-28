#include "../stdafx.h"
#include "Texture.h"



Texture::Texture(std::string filename)
{
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);
	
	unsigned char * image = stbi_load(filename.c_str(), &width, &height, &channels, 4);

	if(image ==NULL)
	{
		std::cout << "error load texture form file " << filename << std::endl;
	}
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, NULL, GL_RGBA, GL_UNSIGNED_BYTE, image);
	

	
	stbi_image_free(image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0+unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}
