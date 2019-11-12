#include "Texture.h"



Texture::Texture()
{
	/*unsigned char* image = SOIL_load_image("../res/")*/
}


Texture::~Texture()
{
	glDeleteTextures(1,&this->id);
}

void Texture::loadFromFile(const char* filename)
{
	FILE * file;
	file = fopen(filename, "rb");

	unsigned int imageSize;
	unsigned int width, height;
}
