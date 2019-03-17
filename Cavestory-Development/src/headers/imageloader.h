#pragma once
#include "gltexture.h"
#include <string>

class imageloader
{
public:
	static gltexture loadPNG(std::string filePath);
};