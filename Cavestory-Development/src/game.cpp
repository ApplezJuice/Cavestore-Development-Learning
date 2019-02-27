/* Game class
	Holds all info for our main game loop
*/

#include <SDL.h>
#include "headers/game.h"
#include "headers/graphics.h"
#include "headers/input.h"
#include <algorithm>

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
	// SDL init is used when you want to modify initializations
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop(); // calls the gameloop from our constructor
}

Game::~Game() // destructor - destroys the game
{

}

void Game::gameLoop() // happens every frame. very important
{
	// create the graphics object
	Graphics graphics;
	Input input;
	// SDL event object, will hold any event that happend during that frames
	SDL_Event event;

	this->_player = Sprite(graphics, "src/content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100);

	int lastUpdateTime = SDL_GetTicks(); // gets the number ms since the sdl library was initialized

	// start the game loop
	while (true)
	{
		// first thing to do, is begin a new frame
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) // runs this if statement if there is an event
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0) // checks to see if a key is not held down
				{
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
			{
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			return;
		}

		// Right before the game closes, it gets the time the whole game loop took
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int elapsedTimeMS = CURRENT_TIME_MS - lastUpdateTime;
		// max frame time is the maximum amount of time you are allowing for a frame
		this->update(std::min(elapsedTimeMS, MAX_FRAME_TIME));
		lastUpdateTime = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();

	this->_player.draw(graphics, 100, 100);

	graphics.flip();
}

void Game::update(float elapsedTime)
{

}