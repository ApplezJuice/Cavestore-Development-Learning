#include "headers/resourceManager.h"
namespace ApplezEng
{
	TextureCache resourceManager::_textureCache;

	gltexture resourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}
