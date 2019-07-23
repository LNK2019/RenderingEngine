#pragma once
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

class Window
{
	SDL_Window*		WindowHandler;
	SDL_GLContext	GLContex;
public:
	Window(const char* Title,int Width, int Height, int XPos = SDL_WINDOWPOS_CENTERED, int YPos = SDL_WINDOWPOS_CENTERED);

	inline void ShowOpenGLVersion() const
	{
		std::cout << "OpenGL version loaded: " << GLVersion.major << "." << GLVersion.minor << std::endl;
	}
	bool WindowIsClosed() const;
private:
	void SetOpenGLContexAttributes();
};