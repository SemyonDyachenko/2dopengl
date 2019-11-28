#include "../stdafx.h"
#include "Display.h"

int main(int argc,char *argv[])
{

	Display display(1440, 900, "From The Darkness Of Night");


	while(!display.IsClosed())
	{
		glClearColor(0.f, 0.f, 25.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		
		display.Update();
		
	}

	

	return 0;
}
