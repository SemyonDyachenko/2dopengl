#ifndef GAME_H
#define GAME_H
#include "../EngineSource/Graphics/Texture.h"
#include "../EngineSource/Shaders/Shader.h"
#include "../EngineSource/Graphics/Mesh.h"

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Game
{
private:
	GLFWwindow* window;
	int framebufferWidth;
	int framebufferHeight;


	GLuint VAO; // vertex array object
	GLuint VBO; // vertex buffer object
	GLuint EBO; // elements buffer object

	unsigned nrOfIndices;
	
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	GameEngine::Texture * texture;

	GameEngine::Mesh * mesh;
	
	GameEngine::Shader * shader;
	

	float deltaTime;
	float currentTime;
	float lastTime;


	void initWindow(const char* winTitle);
	void initGLFW();
	void initGLEW();
	void initOpenGL();
	void initShaders();
	void initTextures();
	void initMeshes();
public:


	
	Game(const char* winTitle);


	~Game();

	
	void update();
	void render();

	void run();
};

#endif