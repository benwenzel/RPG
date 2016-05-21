#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>
//#include "Utils.h"

enum KEYS
{
	LMB,	// <- left mouse button
	RMB,	// <- right mouse button
	LEFT,	// <- left arrow key
	RIGHT,	// <- right arrow key
	UP,		// <- up arrow key
	DOWN,	// <- down array key
	
	KEYCOUNT	// <- the number of values in the enum
};

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	bool processInput();
	void isPressing(int keyCode) const;
	SDL_Point mouseLoc() const {return mouse;}
	
	bool pressing[KEYCOUNT];
	bool locked[KEYCOUNT];
	bool done;
	//Point isoCoords;
	//Point currentTile;
private:
	SDL_Point mouse;
};

#endif
