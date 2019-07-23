#include "Window.h"
#include "cstring"



static bool SDLProcessErrors(const char * FunctionName, const char* FileName, int Line)
{
	const char* ErrorMessage = SDL_GetError();
	if (*ErrorMessage)
	{
		SDL_Log("Error: %s [File: %s] [Line: %s] [Func: %s]", SDL_GetError(), FileName, Line, FunctionName);
		return false;
	}
	return true;
}

Window::Window(const char* Title, int Width, int Height, int XPos /*= SDL_WINDOWPOS_CENTERED*/, int YPos /*= SDL_WINDOWPOS_CENTERED*/)
{
	//SDL Initialization
	int Result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	if (Result != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
	}

	SetOpenGLContexAttributes();
	WindowHandler = SDL_CreateWindow(Title, XPos, YPos, Width, Height, SDL_WINDOW_OPENGL);
	//Window creation
	if (!WindowHandler)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
	}

	GLContex = SDL_GL_CreateContext(WindowHandler);
	//OpenGL contex creation
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_Log("Failed to create OpenGL contex: %s", SDL_GetError());
	}
}

bool Window::WindowIsClosed() const
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_QUIT)
			return true;

		if (Event.type == SDL_KEYDOWN)
		{
			if (Event.key.keysym.sym == SDLK_ESCAPE)
				return true;
		}
	}
	return false;
}

void Window::SetOpenGLContexAttributes()
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
}
