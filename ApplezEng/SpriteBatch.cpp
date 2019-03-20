#include "headers/SpriteBatch.h"

#include <algorithm>

namespace ApplezEng
{

	SpriteBatch::SpriteBatch() :
		_vbo(0), _vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{
		// going to setup any state we need to actually begin rendering
		_sortType = sortType;
		// clear doesn't free all the memory, but resizes it back to 0 so we can write over it
		_renderBatches.clear();
		for (int i = 0; i < _glyphs.size(); i++)
		{
			delete _glyphs[i];
		}
		_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		// sort the glyphs and generate batches from the glyphs
		sortGlyphs();
		createRenderBatches();
	}

	// const reference but we cannot change the original location
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		/*  TL ____ TR
		      |	   |
			  |    |
			BL|____|BR
		dr.x,.y ---> dr.z  ^ = dr.w

		*/

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);

	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(_vao);
		// will loop through our render batches and draw them all
		for (int i = 0; i < _renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		// need to loop through our array of glyphs
		// for each glyph we need to add it to a batch
		// if we get a glyph with a new texture, we need to make a new batch

		std::vector <Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);

		if (_glyphs.empty())
		{
			return;
		}

		int offset = 0;
		int cv = 0; // current vertex
		// emplace creates a new object in render batches without using a copy, way more efficient
		_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);

		vertices[cv++] = _glyphs[0]->topLeft; // will add 1 to CV after the line of code executes
		vertices[cv++] = _glyphs[0]->bottomLeft;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->bottomRight;
		vertices[cv++] = _glyphs[0]->topRight;
		vertices[cv++] = _glyphs[0]->topLeft;
		offset += 6;

		//int cg = 1; // current glyph

		for (int cg = 1; cg < _glyphs.size(); cg++)
		{
			if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) // if the texture is different
			{
				_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
			}
			else
			{
				_renderBatches.back().numVertices += 6; // back is the last element and add 6 more vertices
			}
			vertices[cv++] = _glyphs[cg]->topLeft; // will add 1 to CV after the line of code executes
			vertices[cv++] = _glyphs[cg]->bottomLeft;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->bottomRight;
			vertices[cv++] = _glyphs[cg]->topRight;
			vertices[cv++] = _glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // dynamic draw means you might render it a few times, and might change it
		// upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray()
	{
		// going to create our VAO
		// VAO is a type of object that encapsulates all of the state we need to do rendering with openGL

		if (_vao == 0)
		{
			glGenVertexArrays(1, &_vao);
		}
		// binding it means anything else we do to change the state in here, will be stored in the VAO
		glBindVertexArray(_vao);
		
		if (_vbo == 0)
		{
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		// sending 1 vertex attribute array which is array of positions vertexData - use 0th index (first element of the array)
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

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

		//this is the UV attribute pointer, everytime we have an opengl attribute we have to point it to the data
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// will disable all of the attribs, and unbind the VBO etc.
		glBindVertexArray(0);
		
	}
	void SpriteBatch::sortGlyphs()
	{
		// need to sort based on the sort type
		// can use std::sort or std::stable_sort.
		// stable_sort gurantees that 2 elements that are equal, will retain the same order
		// if 2 elements have the same texture, we can choose which to be drawn first
		switch (_sortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
		}
		
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}
}