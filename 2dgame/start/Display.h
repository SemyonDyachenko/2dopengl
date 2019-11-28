#pragma once


class Display
{
private:
	SDL_Window* window;

	bool isClosed;
public:
	Display(int width, int height, const char* title);

	virtual ~Display();

	bool IsClosed();

	void Update();
};