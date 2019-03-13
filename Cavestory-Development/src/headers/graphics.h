// define the class in the header files
#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>

struct SDL_Window; // forward declaring, can user this names for pointers without being included
struct SDL_Renderer;

class Graphics 
{
public:
	Graphics();
	~Graphics();

	/* SDL_stuface* load image
		loads an image into the _spriteSheets map if it doesn't already exist
		as a result, each image will only ever be loaded once
		returns the image from the map regardless of whether or not it was just loaded
	*/
	SDL_Surface* loadImage(const std::string &filePath);

	/* blitsurface is what draws images to a certain part of the screen
		source is what we are drawing
		source rectangle is what part of the sprite we are drawing
		destination is where we are drawing it to
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
		renders everything to the screen
	*/
	void flip();

	/* void clear
		clears the screen
	*/
	void clear();

	/* SDL_Renderer* getRenderer()
		returns the renderer
	*/
	SDL_Renderer* getRenderer() const;

	/* drawGame
		Will use openGL to draw the graphics to the window
	*/
	void drawGame();


private:
	SDL_Window* _window; // where we are drawing to
	SDL_Renderer* _renderer; // what draws to the window

	// will hold in memory every sprite sheet that we loaded into the game
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif // !GRAPHICS_H
