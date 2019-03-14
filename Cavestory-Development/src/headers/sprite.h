#pragma once

#include <SDL.h>
#include <string>
#include <glew.h>
#include <cstddef>

class Graphics;

/* Sprite Class
	holds all information for individual sprites
*/

class Sprite
{
public:
	Sprite();
	~Sprite();
	
	void init(float x, float y, float width, float height);
	void draw();

private:
	float _x;
	float _y;
	float _width;
	float _height;

	// unsigned int but guranteed to be 32 bits - GL Unsigned Int
	GLuint _vboID;
};

