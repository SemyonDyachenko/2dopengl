#ifndef GAME_H
#define GAME_H
#include "../EngineSource/Graphics/Texture.h"


class Game
{
private:
	GLFWwindow* window;

	GameEngine::Texture * texture;


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