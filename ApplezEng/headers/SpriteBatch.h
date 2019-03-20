#pragma once

#include <glew.h>
#include <glm.hpp>
#include <vector>

#include "vertex.h"

namespace ApplezEng
{
	// texture will sort them by texture
	enum class GlyphSortType
	{
		NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE
	};

	// glyph is a single sprite that will also hold a texture and the depth
	// we need to be able to sort glyphs by texture
	struct Glyph
	{
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};


	class RenderBatch
	{
		// will store the information that it needs to render
		// the specific offset in the VBO
		// we will be able to start somewhere in VBO

	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
			offset(Offset), numVertices(NumVertices), texture(Texture)
		{

		}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};


	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		/* begin will setup everything and get it ready to draw.
			then we will call the draw function and it will add it to the batch, but not draw
			then we will use end that will sort all the images
			then we will render the batch and draw it all to the screen
		*/
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		
		// const reference but we cannot change the original location
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		// a single pointer is just an 8 byte rather than all of the data
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;

	};
}
