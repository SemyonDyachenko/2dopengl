#include "Game.h"




Game::Game() 
{
	


}


Game::~Game()
{

	glfwDestroyWindow(this->window);
	glfwTerminate();
	delete this->shader;
	delete this->texture;
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(4, 4);
	glfwWindowHint(4, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
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


	this->initGlew();
	
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


}



void Game::sceneBuild()
{
	char vertex_file[] = "vertex_core.glsl";
	char fragment_file[] = "fragment_core.glsl";
	
	this->shader = new GameEngine::Shader(vertex_file, fragment_file);


	this->mesh = new GameEngine::Mesh(&Quad(),glm::vec3(0.f),glm::vec3(0.f),glm::vec3(1.f));
	
	
	this->texture = new GameEngine::Texture();
	this->texture->loadFromFile("../res/images/tree.png", GL_TEXTURE_2D);
	
}

void Game::update()
{
		glfwPollEvents();
		//time
		this->currentTime = static_cast<float>(glfwGetTime());
		this->deltaTime = currentTime - lastTime;
		this->lastTime = currentTime;
		
}

void Game::render()
{
	glClearColor(255.f,0.f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	this->shader->useProgram();

	
	
	this->texture->bind(GL_TEXTURE_2D,0);
	
	this->shader->set1i(0, "texture0");
	
	mesh->render(this->shader);
	
	// Swap the screen buffers
	glfwSwapBuffers(window);
	
	glFlush();
	glBindVertexArray(0);
	glEnableVertexAttribArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
 
void Game::run()
{
	
	while (!glfwWindowShouldClose(window))
	{
		this->update();
		this->render();
	}

}