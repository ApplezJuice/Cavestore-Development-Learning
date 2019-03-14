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

	/* drawGame
		Will use openGL to draw the graphics to the window
	*/
	void drawGame();


private:
	SDL_Window* _window; // where we are drawing to
	//SDL_Renderer* _renderer; // what draws to the window

	// will hold in memory every sprite sheet that we loaded into the game
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif // !GRAPHICS_H
