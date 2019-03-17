/* Game class
	Holds all info for our main game loop
*/
#include <glew.h>
#include <SDL.h>
#include "headers/game.h"
#include "headers/input.h"
#include "headers/globals.h"
#include "headers/errors.h"
#include "headers/imageloader.h"

#include <algorithm>
#include <iostream>

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() :
	_time(0.0f), _window(nullptr), _gameState(GameState::PLAY)
{

}

Game::~Game() // destructor - destroys the game
{

}

void Game::run()
{
	initSystems();
	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	_playerTexture = imageloader::loadPNG("src/content/sprites/DungeonCrawlStoneSoupFull/monster/deep_elf_death_mage.png");
	
	gameLoop();
}

void Game::initSystems()
{
	// SDL init is used when you want to modify initializations
	SDL_Init(SDL_INIT_EVERYTHING);

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

	initShaders();
}

void Game::initShaders()
{
	_colorProgram.compileShaders("src/content/shaders/colorShading.vert", "src/content/shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void Game::gameLoop() // happens every frame. very important
{

	
	//this->_player = Sprite(graphics, "src/content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100);

	int lastUpdateTime = SDL_GetTicks(); // gets the number ms since the sdl library was initialized

	// start the game loop
	while (_gameState != GameState::EXIT)
	{
		processInput();
		_time += 0.03f;
		drawGame();
		// Right before the game closes, it gets the time the whole game loop took
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int elapsedTimeMS = CURRENT_TIME_MS - lastUpdateTime;
		// max frame time is the maximum amount of time you are allowing for a frame
		this->update(std::min(elapsedTimeMS, MAX_FRAME_TIME));
		lastUpdateTime = CURRENT_TIME_MS;
	}
}

void Game::update(float elapsedTime)
{

}

void Game::processInput()
{
	Input input;
	// SDL event object, will hold any event that happend during that frames
	SDL_Event evnt;

	// first thing to do, is begin a new frame
	input.beginNewFrame();

	if (SDL_PollEvent(&evnt)) // runs this if statement if there is an event
	{
		switch(evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:
			if (evnt.key.repeat == 0) // checks to see if a key is not held down
			{
				input.keyDownEvent(evnt);
			}
			break;

		case SDL_KEYUP:
			input.keyUpEvent(evnt);
			break;

		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
	if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
	{
		_gameState = GameState::EXIT;
	}
}

void Game::drawGame()
{
	{
		// tells openGL the depth it should clear to
		glClearDepth(1.0);

		// clears the color from the screen
		// bitwise OR to clear the depth and color buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_colorProgram.use();
		// bind the texture and use the 1st texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _playerTexture.id);
		// 1i for interger
		GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
		// using gl active texture 0
		glUniform1i(textureLocation, 0);

		// set the uniform before the draw
		// name of the uniform set in the shader, for this instance it is time
		//GLint timeLocation = _colorProgram.getUniformLocation("time");

		// need to send time to the GFX card
		// glUniform and then the type, 1f = 1 float, 3fv = 3 float vector
		// need the location which is timeLocation and then the actual float which is _time
		//glUniform1f(timeLocation, _time);

		// draw the sprite!
		_sprite.draw();

		glBindTexture(GL_TEXTURE_2D, 0);
		_colorProgram.unUse();

		// Will swap the buffer and draw window
		SDL_GL_SwapWindow(_window);
	}
}