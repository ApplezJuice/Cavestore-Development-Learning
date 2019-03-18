#pragma once

#include "TextureCache.h"
#include <string>
namespace ApplezEng
{
	class resourceManager
	{
	public:
		static gltexture getTexture(std::string texturePath);


	private:
		static TextureCache _textureCache;
	};
}

