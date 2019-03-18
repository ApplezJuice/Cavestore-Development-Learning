#include "headers/Window.h"
#include "headers/errors.h"


namespace ApplezEng
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		else if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		else if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);


		if (_sdlWindow == nullptr)
		{
			fatalError("SDL Window could not be creates!");
		}

		// Sets up openGL context for us to be able to use openGL
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			fatalError("SDL_GL Context could not be created!");
		}

		// Initialize glew
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize glew!");
		}

		// see the version of OpenGL from the host, incase it isn't working on the PC that has the game
		std::printf("***    OpenGL Version: %s    ***\n", glGetString(GL_VERSION));

		// What color we will swap to when we call the clear functions
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// vsync was enabled by default but here is how to enable it
		// if it is set to 1, vsync is on, if it is 0, it is off
		SDL_GL_SetSwapInterval(0);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}