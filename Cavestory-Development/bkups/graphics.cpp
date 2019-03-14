#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>

#include "headers/graphics.h"
#include "headers/globals.h"
#include "headers/sprite.h"

#include <string>
#include <iostream>

/* Graphics class
	Holds all information dealing with graphics for the game
*/

// constructor needs to create the window and display some stuff

void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

Graphics::Graphics() 
{
	//SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,0, &this->_window, &this->_renderer);

	//Using openGL to render the window instead of SDL
	_window = SDL_CreateWindow("Unkown Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	if (_window == nullptr)
	{
		fatalError("SDL Window could not be creates!");
	}

	// Sets up openGL context for us to be able to use openGL
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
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

	// Tells SDL to double buffer. Instead of have 1 window pane, we will have 2
	// 1 where we will be drawing to, and 1 where we will be clearing
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// What color we will swap to when we call the clear functions
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//SDL_SetWindowTitle(this->_window, "Project Unkown"); // names the window
}

Graphics::~Graphics() 
{
	SDL_DestroyWindow(this->_window);
}


void Graphics::drawGame()
{
	Sprite _sprite;
	// tells openGL the depth it should clear to
	glClearDepth(1.0);

	// clears the color from the screen
	// bitwise OR to clear the depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_sprite.draw();

	// Will swap the buffer and draw window
	SDL_GL_SwapWindow(_window);
}