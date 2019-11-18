#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>


namespace GameEngine
{

	class Shader
	{
	private:
		GLuint id;

		//const int versionMajor;
		//const int versionMinor;
		
		std::string loadShaderSource(char* filename);
		GLuint loadShader(GLenum target, char*filename);
		void linkProgram(GLuint vertexShader, GLuint fragmentShader);
	public:
		Shader(/*const int versionMajor, const int versionMinor,*/ char* vertexFile, char* fragmentFile);

		virtual ~Shader();

		/*void loadFromFile(const char* vertex_file_name, const char* fragment_file_name);*/

		void useProgram();

		void unuseProgram();

		void set1i(GLint value, const GLchar* name);

		void set1f(GLfloat value, const GLchar* name);

		void setVec2f(glm::fvec2 value, const GLchar* name);

		void setVec3f(glm::fvec3 value, const GLchar* name);

		void setVec4f(glm::fvec4 value, const GLchar* name);
		
		void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);

		void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	};
	
}

#endif