#include "Game.h"



Game::Game()
{
	
}


Game::~Game()
{
}

bool Game::init(const char* winTitle)
{
	if (!glfwInit())
	{
		std::cout << "Error init GLFW .." << std::endl;
		return false;
	}
	this->SCREEN_WIDTH = 1440;
	this->SCREEN_HEIGHT = 900;

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, winTitle,NULL,NULL);
	if(window == NULL)
	{
		std::cout << "Error creating window" << std::endl;
		return false;
	}

	//OPENGL
	glfwMakeContextCurrent(this->window);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(1);

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(this->window,xPos, yPos);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Game::update()
{
		glfwPollEvents();
}

void Game::render()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glfwSwapBuffers(this->window);
}

