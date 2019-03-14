#include "headers/sprite.h"
#include "headers/globals.h"
#include "headers/vertex.h"

Sprite::Sprite() 
{
	_vboID = 0;

}


Sprite::~Sprite()
{
	// free the vertex buffer now that we destroyed the sprite
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;


	if (_vboID == 0) 
	{
		// generates a random unique gl buffer
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	// First triangle
	vertexData[0].pos.x = x + width;
	vertexData[0].pos.y = y + height;

	vertexData[1].pos.x = x;
	vertexData[1].pos.y = y + height;

	vertexData[2].pos.x = x;
	vertexData[2].pos.y = y;

	// Second Triangle
	vertexData[3].pos.x = x;
	vertexData[3].pos.y = y;

	vertexData[4].pos.x = x + width;
	vertexData[4].pos.y = y;

	vertexData[5].pos.x = x + width;
	vertexData[5].pos.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].color.r = 255;
		vertexData[i].color.b = 0;
		vertexData[i].color.g = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	// binds the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// tells what data to put on the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// unbinds the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() 
{
	// binds the buffer, can only have 1 gl array buffer active at 1 time
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// sending 1 vertex attribute array which is array of positions vertexData - use 0th index (first element of the array)
	glEnableVertexAttribArray(0);

	// tells opengl where the start of our data is. We gave it the vboID but we may only want to draw a certain part
	// 2 stands for x, and y coordinate
	// this is the position attribute pointer
	// glsize stride is the size of the vertex, which is the size of our Vertex struct
	// the last parameter is the offset in bytes of the position inside the vertex struct. i.e. the position is 0 because it is in front.
	// when we do the color, there are 8 bytes in front of it, so it would need an offset of 8
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	// this is the color attrib pointer
	// normalize means to make it between a range of 0-1
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	// now to draw the data
	// drawing 6 verticies with 2 floats in each (12)
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// disables it
	glDisableVertexAttribArray(0);

	// unbinds the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}