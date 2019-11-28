#include "../stdafx.h"
#include "Display.h"
#include "../graphics/Shader.h"
#include "../graphics/Mesh.h"
#include "../graphics/Texture.h"

int main(int argc,char *argv[])
{
	

	

	
	Display display(1440, 900, "From The Darkness Of Night");

	Vertex vertices[] = {
		Vertex(
			glm::vec3(-0.5,-0.5,0),
			glm::vec2(0.0,0.0)
		),
		Vertex(
			glm::vec3(0,0.5,0),
			glm::vec2(0.5,1.0)
		),
		Vertex(
			glm::vec3(0.5,-0.5,0),
			glm::vec2(1.0,0.0)
		),
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Texture texture("../res/images/grass.jpg");

	Shader shader("shader.vs","shader.fs");
	
	while(!display.IsClosed())
	{
		glClearColor(0.f, 0.f, 25.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
		texture.Bind(0);
		mesh.Render();
		
		display.Update();
		
	}

	

	return 0;
}
