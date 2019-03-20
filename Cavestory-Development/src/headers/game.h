#pragma once

#include <ApplezEng/headers/ApplezEng.h>
#include <ApplezEng/headers/sprite.h>
#include <ApplezEng/headers/gltexture.h>
#include <ApplezEng/headers/glslProgram.h>
#include <ApplezEng/headers/Window.h>
#include <ApplezEng/headers/Camera2D.h>
#include <ApplezEng/headers/SpriteBatch.h>

#include <vector>

class Graphics;

enum class GameState {PLAY, EXIT};

class Game
{
public: // need to define public for classes
	Game();
	~Game();

	void run();
	
private:
	ApplezEng::Window _window;
	void initSystems();
	void initShaders();
	void gameLoop();
	//void draw(Graphics &graphics);
	void update(float elapsedTime);
	void processInput();
	void drawGame();
	void calculateFPS();

	GameState _gameState;

	//std::vector <ApplezEng::Sprite*> _sprites;

	ApplezEng::glslProgram _colorProgram;
	ApplezEng::Camera2D _camera;
	ApplezEng::SpriteBatch _spriteBatch;

	float _fps;
	float _maxFPS;
	float _frameTime;

	float _time;
};


