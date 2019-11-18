#include "Shader.h"



namespace GameEngine
{

	std::string Shader::loadShaderSource(char* filename)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		//Vertex
		in_file.open(filename);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE: " << filename << "\n";
		}

		in_file.close();

		return src;
	}

	GLuint Shader::loadShader(GLenum target, char* filename)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(target);
		std::string str_src = this->loadShaderSource(filename);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER: " << filename << "\n";
			std::cout << infoLog << "\n";
		}

		return shader;
	}

	void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);


		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << "\n";
			std::cout << infoLog << "\n";
		}

		glUseProgram(0);
	}


	Shader::Shader( char* vertexFile,  char* fragmentFile)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(this->id);
	}

	void Shader::useProgram()
	{
		glUseProgram(this->id);
	}

	void Shader::unuseProgram()
	{
		glUseProgram(0);
	}

	void Shader::set1i(GLint value, const GLchar * name)
	{
		this->useProgram();
		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuseProgram();
	}

	void Shader::set1f(GLfloat value, const GLchar * name)
	{
		this->useProgram();
		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuseProgram();
	}

	void Shader::setVec2f(glm::fvec2 value, const GLchar * name)
	{
		this->useProgram();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuseProgram();
	}

	void Shader::setVec3f(glm::fvec3 value, const GLchar * name)
	{
		this->useProgram();
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuseProgram();
	}

	void Shader::setVec4f(glm::fvec4 value, const GLchar * name)
	{
		this->useProgram();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuseProgram();
	}

	void Shader::setMat3fv(glm::mat3 value, const GLchar * name, GLboolean transpose)
	{
		this->useProgram();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuseProgram();
	}

	void Shader::setMat4fv(glm::mat4 value, const GLchar * name, GLboolean transpose)
	{
		this->useProgram();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuseProgram();
	}

}

