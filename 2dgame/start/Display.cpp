#include "../stdafx.h"
#include "Display.h"

Display::Display(int width, int height, const char * title)
{
	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	
	this->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);

	SDL_GL_CreateContext(this->window);

	GLenum glew = glewInit();
	if(glew != GLEW_OK)
	{
		std::cerr << "Glew failed init" << std::endl;
	}

	this->isClosed = false;

}

Display::~Display()
{
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool Display::IsClosed()
{
	return isClosed;
}

void Display::Update()
{

	SDL_GL_SwapWindow(this->window);

	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			this->isClosed = true;
		}
	}
}
