#include <SDL.h>
#include <SDL_image.h>

#include "headers/graphics.h"
#include "headers/globals.h"

/* Graphics class
	Holds all information dealing with graphics for the game
*/

// constructor needs to create the window and display some stuff

Graphics::Graphics() 
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH,globals::SCREEN_HEIGHT,0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory"); // names the window
}

Graphics::~Graphics() 
{
	SDL_DestroyWindow(this->_window);
}

SDL_Surface * Graphics::loadImage(const std::string & filePath)
{
	// gets the count of the spreadsheet from the file path
	// if it does not see anything, thus 0, we add it
	if (this->_spriteSheets.count(filePath) == 0)
	{
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture * texture, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle)
{
	// copies what you pass it to the renderer
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
	// draws it to the screen
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return this->_renderer;
}
