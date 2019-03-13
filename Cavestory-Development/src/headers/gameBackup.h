#pragma once
#ifndef GAME_H
#define GAME_H

#include "sprite.h"

class Graphics;

class Game
{
public: // need to define public for classes
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Sprite _player;
};

#endif // !GAME_H

