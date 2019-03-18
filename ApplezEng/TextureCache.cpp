#include "headers/TextureCache.h"
#include "headers/imageloader.h"
#include <iostream>

namespace ApplezEng
{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	gltexture TextureCache::getTexture(std::string texturePath)
	{
		// scan the texture map via a binary tree
		// if it reaches a nullptr it returns a map.end()
		// std::map<std::string, gltexture>::iterator mit = auto
		// lookups the texture and sees if it is in the map
		auto mit = _textureMap.find(texturePath);

		// check if its not in the map
		if (mit == _textureMap.end())
		{
			// load it into the map
			gltexture newTexture = imageloader::loadPNG(texturePath);

			// pair is 2 values combined together
			//std::pair<std::string, gltexture> newPair(texturePath, newTexture);
			// insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));
			std::cout << "Loaded texture!\n";
			return newTexture;
		}

		// if it is in the map and mit found it
		// mit is a pointer so we need -> and it returns a pair.
		// we need to specify what we return, first is a key, second is a value
		// we want the value
		std::cout << "Loaded cached texture!\n";
		return mit->second;
	}
}
