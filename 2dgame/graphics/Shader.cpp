#include "../stdafx.h"
#include "Shader.h"


void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error)
{
	GLint success = 0;
	GLchar errors[1024] = { 0 };
	if(isProgram)
	{
		glGetProgramiv(shader, flag, &success);	
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if(success == GL_FALSE)
	{
		if(isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(errors), NULL, errors);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, errors);
		}

		std::cerr << error << ": '" << "errors" << "'" << std::endl;
	}
}

std::string Shader::loadShader(const std::string& filename)
{
	std::ifstream file;
	file.open((filename).c_str());

	std::string out;
	std::string line;

	if(file.is_open())
	{
		while(file.good())
		{
			std::getline(file, line);
			out.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Error to load Shader: " << filename << std::endl;
	}

	return out;
}

GLuint Shader::createShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if(shader == 0)
	{
		std::cout << "Error: Shader creation filed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLength[1];
	shaderSourceStringLength[0] = text.length();
	shaderSourceStrings[0] = text.c_str();


	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, true, "Error: Shader is invalid");
	
	return shader;
}

Shader::Shader(const std::string& vertex_file, const std::string& fragment_file)
{
	this->program = glCreateProgram();
	this->shaders[0] = createShader(loadShader(vertex_file), GL_VERTEX_SHADER);
	this->shaders[1] = createShader(loadShader(fragment_file), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUMBER_OF_SHADER;i++)
	{
		glAttachShader(program, shaders[i]);
	}


	glLinkProgram(this->program);
	checkShaderError(program, GL_LINK_STATUS, true, "Error: Shader filed to link");

	glValidateProgram(this->program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader is invalid");
}

void Shader::Bind()
{
	glUseProgram(this->program);
}

Shader::~Shader()
{
	for(unsigned int i = 0;i < NUMBER_OF_SHADER;i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(this->program);
}
