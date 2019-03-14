#pragma once

#include <SDL.h>
#include <map>

class Input
{
public:
	void beginNewFrame(); // will be called at the begining of every frame
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	// a map holds 2 types of related information together
	// SDL scancode relates the spot of the keyboard to the position
	// exmaple, not everyone has the same placement for the A key
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};

