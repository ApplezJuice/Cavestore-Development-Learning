#pragma once

#include <glew.h>

// creating a struct of type Pos and it's creating an instance of it called 'pos'
// this is called composition
struct Pos
{
	float x;
	float y;
};

struct Color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV
{
	float u;
	float v;
};

struct Vertex
{
	/*
		Struct Color {
		...
		} color;
		Color color; - The code above is a shortcut to create an instance of the struct Color
	*/
	Pos pos;
	Color color;

	// UV texture coordinates
	UV uv;

	void setPosition(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
};