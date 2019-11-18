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

	GameEngine::Texture * texture;

	GameEngine::Mesh * mesh;
	
	GameEngine::Shader * shader;
	
	GLuint VAO,VBO,EBO;

	float deltaTime;
	float currentTime;
	float lastTime;
public:

	
	 int SCREEN_WIDTH;
	 int SCREEN_HEIGHT;
	
	Game();
	~Game();

	void initGlfw();
	void initGlew();
	void init(const char* winTitle);

	void sceneBuild();
	
	void update();
	void render();

	void run();
};

#endif