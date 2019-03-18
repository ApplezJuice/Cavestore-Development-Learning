#include <SDL.h>
#include <glew.h>
#include "headers/ApplezEng.h"
namespace ApplezEng
{
	int init()
	{
		// SDL init is used when you want to modify initializations
		SDL_Init(SDL_INIT_EVERYTHING);

		// Tells SDL to double buffer. Instead of have 1 window pane, we will have 2
		// 1 where we will be drawing to, and 1 where we will be clearing
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}