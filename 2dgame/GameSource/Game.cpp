#include "Game.h"



Game::Game() 
{
	


}


Game::~Game()
{
}

void Game::initGlfw()
{
	if (!glfwInit())
	{
		std::cout << "Error init GLFW .." << std::endl;
		glfwTerminate();
	}
}

void Game::initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	//Error
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}
}

void Game::init(const char* winTitle)
{
	glfwMakeContextCurrent(window);
	
	this->initGlfw();
	
	this->SCREEN_WIDTH = 1440;
	this->SCREEN_HEIGHT = 900;

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, winTitle,NULL,NULL);
	


	//OPENGL
	glfwMakeContextCurrent(this->window);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(1);

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(this->window,xPos, yPos);

	this->initGlew();
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, width, height, 0, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void Game::sceneBuild()
{
	this->texture = new GameEngine::Texture();
	this->texture->loadFromFile("../res/images/tree.png", GL_TEXTURE_2D);
}

void Game::update()
{
		glfwPollEvents();
		this->deltaTime = currentTime - lastTime;
		
}

void Game::render()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->texture->bind(GL_TEXTURE_2D,0);

	glfwSwapBuffers(this->window);
	glFlush();
}
 
void Game::run()
{
	
	while (!glfwWindowShouldClose(window))
	{
		this->update();
		this->render();
	}

}