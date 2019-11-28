#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb/stb_image.h"

class Texture
{
private:
	GLuint texture;
public:
	Texture(std::string filename);
	
	~Texture();

	void Bind(unsigned int unit);
	
};


#endif
