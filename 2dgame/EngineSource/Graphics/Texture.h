#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <SOIL2.h>




namespace GameEngine
{


	class Texture
	{
	private:
		GLuint id;
		int width;
		int height;
		unsigned int type;
	public:
		Texture();

		virtual ~Texture();

		//functions
		void loadFromFile(const char* filename,GLenum target);

		inline GLuint getID() const;

		void bind(GLenum target,GLint t_uint);

		void unbind(GLenum target);
	};

}


#endif 
