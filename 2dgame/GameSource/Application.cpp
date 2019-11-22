#include "../../stdafx.h"
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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, true);
	
	//if(this->fullscreen)
		//this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, winTitle, glfwGetPrimaryMonitor(), NULL);
	//else
		this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, winTitle, NULL, NULL);

	
	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	

	glfwGetFramebufferSize(this->window, &this->WINDOW_WIDTH, &this->WINDOW_HEIGHT);

	glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

Application::Application()
{
	this->WINDOW_WIDTH = 1440;
	this->WINDOW_HEIGHT = 900;

	this->initGLFW();
	this->initWindow("From The Darkness Of Night", false);
	this->initGLEW();
	this->initOpenGL();

	this->renderer = new Engine::Renderer();
}


Application::~Application()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Application::UpdateDeltaTime()
{

	this->currentTime = static_cast<float>(glfwGetTime());
	this->deltaTime = currentTime - lastTime;
	this->lastTime = currentTime;
}

void Application::UpdateInput()
{
	
}

void Application::Update()
{
	glfwPollEvents();
	this->UpdateInput();
	this->UpdateDeltaTime();
}

void Application::Render()
{
	this->renderer->clear();


	glfwSwapBuffers(window);

	glFlush();
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		this->Update();
		this->Render();
	}
}
