#pragma once

#include "sprite.h"
#include "gltexture.h"
#include "headers/glslProgram.h"

class Graphics;

enum class GameState {PLAY, EXIT};

class Game
{
public: // need to define public for classes
	Game();
	~Game();

	void run();
	
private:
	SDL_Window* _window;
	void initSystems();
	void initShaders();
	void gameLoop();
	//void draw(Graphics &graphics);
	void update(float elapsedTime);
	void processInput();
	void drawGame();

	GameState _gameState;

	Sprite _sprite;

	glslProgram _colorProgram;
	gltexture _playerTexture;

	float _time;
};


