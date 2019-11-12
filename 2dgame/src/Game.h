#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "iostream"

class Game
{
private:
	GLFWwindow* window;
public:
	 int SCREEN_WIDTH;
	 int SCREEN_HEIGHT;
	
	Game();
	~Game();

	bool init(const char* winTitle);
	
	void update();
	void render();
};

#endif