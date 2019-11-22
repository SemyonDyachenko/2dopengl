#include "../../stdafx.h"
#include "Texture.h"


namespace Engine
{

	Texture::Texture(GLenum target)
	{
		this->target = target;
	}

	GLint& Texture::getUnit()
	{
		return this->unit;
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	void Texture::loadFromFile(const char* path)
	{

		unsigned char* image = SOIL_load_image(path, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &id);
		glBindTexture(target, id);

		glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{

			glTexImage2D(target, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(target);

		}
		else
		{
			std::cout << "GAME ENGINE::Texture class:: ERROR:: TEXTURE_LOADING_FAILED ,try check path to image file" << "\n";
		}

		glActiveTexture(0);
		glBindTexture(target, 0);
		SOIL_free_image_data(image);
	}

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, this->id);
	}

	void Texture::unbind()
	{
		glActiveTexture(0);
		glBindTexture(this->target, 0);
	}
}
