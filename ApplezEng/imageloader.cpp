#include "headers/imageloader.h"
#include "headers/picopng.h"
#include "headers/iomanager.h"
#include "headers/errors.h"
namespace ApplezEng
{
	gltexture imageloader::loadPNG(std::string filePath)
	{
		// inits everything to 0
		gltexture texture = {};

		std::vector<unsigned char> in;
		std::vector<unsigned char> out;

		unsigned long width, height;

		if (iomanager::readFileToBuffer(filePath, in) == false)
		{
			fatalError("Failed to load PNG file to buffer");
		}

		int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
		if (errorCode != 0)
		{
			fatalError("decodePNG failed with error: " + std::to_string(errorCode));
		}

		// generates an id for the texture
		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		// takes the buffer of pixels (out) and upload it to the openGL texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		// set some parameters to tell openGL how the texture should be treated
		// how we want the texture to wrap on 1 image, do we want to clamp or repeat etc.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// gl texture mag filter has to do with mip mapping
		// based on the size of the texture, it is going to use linear interpolation
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// mip mapping is when we take the texutre, and progressively make the samples smaller as the texture is smaller on the screen
		// no reason to display a texture with a lot of pixels when it is small
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}
