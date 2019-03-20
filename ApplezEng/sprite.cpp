#include "headers/sprite.h"
#include "headers/globals.h"
#include "headers/vertex.h"
#include "headers/resourceManager.h"


namespace ApplezEng
{
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

	void Sprite::init(float x, float y, float z, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_z = z;
		_width = width;
		_height = height;

		// load the texture via resource manager
		_Texture = resourceManager::getTexture(texturePath);

		if (_vboID == 0)
		{
			// generates a random unique gl buffer
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		// First triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		// Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].color.r = 255;
			vertexData[i].color.b = 0;
			vertexData[i].color.g = 0;
			vertexData[i].color.a = 255;
		}

		vertexData[1].setColor(0, 255, 0, 255);
		vertexData[4].setColor(0, 0, 255, 255);

		// binds the vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		// tells what data to put on the buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// unbinds the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		// bind the texture
		// we don't want to unbind the texture
		glBindTexture(GL_TEXTURE_2D, _Texture.id);

		// binds the buffer, can only have 1 gl array buffer active at 1 time
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);



		// now to draw the data
		// drawing 6 verticies with 2 floats in each (12)
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// disables it
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// unbinds the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}