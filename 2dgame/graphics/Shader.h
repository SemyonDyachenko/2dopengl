#ifndef SHADER_H
#define SHADER_H


class Shader
{
private:
	static const unsigned int NUMBER_OF_SHADER = 2;
	
	GLuint program;
	GLuint shaders[NUMBER_OF_SHADER];

	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & error);
	std::string loadShader(const std::string & filename);

	GLuint createShader(const std::string & text, GLenum shaderType);
	
public:
	Shader(const std::string & vertex_file,const std::string & fragment_file);

	void Bind();


	
	virtual ~Shader();
};



#endif