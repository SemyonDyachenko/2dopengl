#include "Application.h"


void Application::initGLFW()
{
	if(!glfwInit())
	{
		std::cout << "GAME::ERROR::FAILED INIT GLFW " << std::endl;
	}
}

void Application::initGLEW()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

	}
}

void Application::initOpenGL()
{
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

void Application::initWindow(const char* winTitle,bool fullscreen)
{
	if(this->fullscreen)
		this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, winTitle, glfwGetPrimaryMonitor(), NULL);
	else
		this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, winTitle, NULL, NULL);
}

Application::Application()
{
	this->WINDOW_WIDTH = 1440;
	this->WINDOW_HEIGHT = 900;

	this->initGLFW();
	this->initWindow("From The Darkness Of Night", false);
	this->initGLEW();
	this->initOpenGL();
	
}


Application::~Application()
{
}

void Application::UpdateDeltaTime()
{

	this->currentTime = glfwGetTime();
	this->deltaTime = currentTime - lastTime;
	this->lastTime = currentTime;
}

void Application::UpdateInput()
{
	
}

void Application::Update()
{
	this->UpdateInput();
	this->UpdateDeltaTime();
}

void Application::Render()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glfwSwapBuffers(this->window);
	glFlush();
}

void Application::Run()
{
	while (glfwWindowShouldClose(this->window))
	{
		this->Update();
		this->Render();
	}
}
