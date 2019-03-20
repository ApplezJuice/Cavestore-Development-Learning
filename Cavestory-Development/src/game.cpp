/* Game class
	Holds all info for our main game loop
*/
#include <glew.h>
#include <SDL.h>
#include "headers/game.h"
#include <ApplezEng/headers/input.h>
#include <ApplezEng/headers/globals.h>
#include <ApplezEng/headers/errors.h>
#include <ApplezEng/headers/resourceManager.h>
#include <ApplezEng/headers/vertex.h>

#include <algorithm>
#include <iostream>

Game::Game() :
	_time(0.0f), _gameState(GameState::PLAY), _maxFPS(60.0f)
{
	_camera.init(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
}

Game::~Game() // destructor - destroys the game
{
	/*while (!_sprites.empty())
	{
		delete _sprites.back();
		_sprites.pop_back();
	}*/
}

void Game::run()
{
	initSystems();
	//_sprites.push_back(new ApplezEng::Sprite());
	//_sprites.back()->init(0.0f, 0.0f, 0.0f, 32.0f, 32.0f, "src/content/sprites/DungeonCrawlStoneSoupFull/monster/deep_elf_death_mage.png");

	//_sprites.push_back(new ApplezEng::Sprite());
	//_sprites.back()->init(100.0f, 0.0f, 0.0f, 32.0f, 32.0f, "src/content/sprites/DungeonCrawlStoneSoupFull/monster/deep_elf_death_mage.png");

	gameLoop();
}

void Game::initSystems()
{
	ApplezEng::init();

	_window.createWindow("Project Lynx", globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0);

	initShaders();

	_spriteBatch.init();
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
	_camera.setPosition(_camera.getPosition() + glm::vec3(
		globals::SCREEN_WIDTH / 2.0f,
		globals::SCREEN_HEIGHT / 2.0f,
		0.0f
	));
	// start the game loop
	while (_gameState != GameState::EXIT)
	{
		// used for frame time measuring
		float startTicks = SDL_GetTicks();

		processInput();
		_time += 0.03f;

		_camera.update();

		drawGame();
		calculateFPS();

		// print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10){
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		// amount of time for 1 game loop cycle
		float frameTicks = SDL_GetTicks() - startTicks;
		// limit the FPS to the MAX FPS
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay((1000.0f / _maxFPS) - frameTicks);
		}
	}
}

void Game::update(float elapsedTime)
{

}

void Game::processInput()
{
	ApplezEng::Input input;
	// SDL event object, will hold any event that happend during that frames
	SDL_Event evnt;

	const float CAMERA_SPEED = 5.0f;

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
			//if (evnt.key.repeat == 0) // checks to see if a key is not held down
			//{
			//	input.keyDownEvent(evnt);
			//}
			switch (evnt.key.keysym.sym)
			{
			case SDLK_w:
				_camera.setPosition(_camera.getPosition() + glm::vec3(0.0f, -CAMERA_SPEED, 0.0f));
				break;
			case SDLK_s:
				_camera.setPosition(_camera.getPosition() + glm::vec3(0.0f, CAMERA_SPEED, 0.0f));
				break;
			case SDLK_a:
				_camera.setPosition(_camera.getPosition() + glm::vec3(CAMERA_SPEED, 0.0f, 0.0f));
				break;
			case SDLK_d:
				_camera.setPosition(_camera.getPosition() + glm::vec3(-CAMERA_SPEED, 0.0f, 0.0f));
				break;
			case SDLK_ESCAPE:
				_gameState = GameState::EXIT;
				break;
			}
			break;

		case SDL_KEYUP:
			input.keyUpEvent(evnt);
			break;

		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}
	}
	/*if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
	{
		_gameState = GameState::EXIT;
	}*/
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
		// 1i for interger
		GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
		// using gl active texture 0
		glUniform1i(textureLocation, 0);

		// set the uniform before the draw
		// name of the uniform set in the shader, for this instance it is time
		GLint timeLocation = _colorProgram.getUniformLocation("time");

		// need to send time to the GFX card
		// glUniform and then the type, 1f = 1 float, 3fv = 3 float vector
		// need the location which is timeLocation and then the actual float which is _time
		glUniform1f(timeLocation, _time);

		//set the camera matrix
		GLint pLocation = _colorProgram.getUniformLocation("P");
		// using gl active texture 0
		glm::mat4 cameraMatrix = _camera.getCameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		_spriteBatch.begin();

		glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
		glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static ApplezEng::gltexture texture = ApplezEng::resourceManager::getTexture("src/content/sprites/DungeonCrawlStoneSoupFull/monster/deep_elf_death_mage.png");
		ApplezEng::Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		color.a = 255;

		// draw our batches
		for (int i = 0; i < 3000; i++)
		{
			_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
			_spriteBatch.draw(pos + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
		}
		

		_spriteBatch.end();

		_spriteBatch.renderBatch();

		// draw the sprite!
		/*for (int i = 0; i < _sprites.size(); i++)
		{
			_sprites[i]->draw();
		}*/

		glBindTexture(GL_TEXTURE_2D, 0);
		_colorProgram.unUse();

		// Will swap the buffer and draw window
		_window.swapBuffer();
	}
}

void Game::calculateFPS()
{
	// static = initialized once and retain state even when exiting function
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - previousTicks;
	// mod % gets remainder
	// if num_samples is 3 and current frame as soon is it hits the num samples the modulo returns 0 creating a circle
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	previousTicks = currentTicks;

	int count;
	currentFrame++;

	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		// sum of the array of frameTimes with the number of samples
		frameTimeAverage += frameTimes[i];
	}
	// get the average time of the frames
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		// 1000 ms in a second / frametimeaverage is our FPS
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
}
