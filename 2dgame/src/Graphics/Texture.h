#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Texture
{
private:
	GLuint id;
	int width;
	int height;
	
public:
	Texture();
	
	~Texture();

	//functions
	void loadFromFile(const char* filename);
};

#endif 