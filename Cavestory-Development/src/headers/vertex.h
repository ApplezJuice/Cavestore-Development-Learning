#pragma once

#include <glew.h>

struct Vertex
{
	// creating a struct of type Pos and it's creating an instance of it called 'pos'
	// this is called composition
	struct Pos
	{
		float x;
		float y;
	} pos;

	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
};