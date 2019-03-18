#pragma once
#include "gltexture.h"
#include <string>
namespace ApplezEng
{
	class imageloader
	{
	public:
		static gltexture loadPNG(std::string filePath);
	};
}