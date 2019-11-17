#ifndef ENGINE_SHADER_H

#define ENGINE_SHADER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace GameEgnine
{

	class Shader
	{
	private:
		GLuint id;
	public:
		Shader();

		virtual ~Shader();

		void loadFromFile(const char* vertex_file_name, const char* fragment_file_name);

		void useProgram();

	};
	
}

#endif