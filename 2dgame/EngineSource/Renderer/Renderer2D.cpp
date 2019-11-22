#include "../../stdafx.h"
#include "Renderer2D.h"

namespace Engine
{


	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::clear()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}


}