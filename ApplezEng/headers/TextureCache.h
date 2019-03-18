#pragma once

#include <map>
#include "gltexture.h"
namespace ApplezEng
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		gltexture getTexture(std::string texturePath);

	private:
		// creating a map to hold the textures
		std::map<std::string, gltexture> _textureMap;
	};
}

