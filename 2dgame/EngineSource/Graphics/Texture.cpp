#include "Texture.h"


namespace GameEngine
{

	Texture::Texture()
	{
		this->width = 0;
		this->height = 0;
		
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	void Texture::loadFromFile(const char* filename,GLenum target)
	{
		int channels = NULL;
		unsigned char* image = SOIL_load_image(filename, &this->width, &this->height, &channels, SOIL_LOAD_RGBA);
		
		glGenTextures(1, &id);
		glBindTexture(target, id);

		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if(image)
		{
			
			glTexImage2D(target, 0, GL_RGBA, this->width, this->height, 0,GL_RGBA, GL_UNSIGNED_BYTE, image);
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

	GLuint Texture::getID() const
	{
		return this->id;
	}

	void Texture::bind(GLenum target,GLint t_uint)
	{
		glActiveTexture(GL_TEXTURE0+t_uint);
		glBindTexture(target, this->id);
	}

	void Texture::unbind(GLenum target)
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

}