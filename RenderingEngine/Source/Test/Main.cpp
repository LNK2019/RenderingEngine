#define SDL_MAIN_HANDLED

#include "Window.h"
#include <iostream>

int main(int argc, char** argv)
{
	Window MainWindow("TestWindow",500,500);
	MainWindow.ShowOpenGLVersion();

	while (!MainWindow.WindowIsClosed())
	{
		
	}
	return 0;
}