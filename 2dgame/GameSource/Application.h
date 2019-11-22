#include <GL/glew.h>
#include "GLFW/glfw3.h"


#include <iostream>

class Application
{
private:
	//std::stack<State*> states;

	GLFWwindow * window;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	bool fullscreen;

	// time
	float currentTime;
	float lastTime;
	float deltaTime;

	//initialization functions
	void initGLFW();
	void initGLEW();
	void initOpenGL();
	void initWindow(const char* winTitle,bool fullscreen);
	
public:
	Application();
	
	
	~Application();
	
	void UpdateDeltaTime();
	
	void UpdateInput();
	
	void Update();
	
	void Render();
	
	void Run();
};

