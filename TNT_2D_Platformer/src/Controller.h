#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <SDL.h>

class Controller
{
private:
	static const Uint8* _key_state;

public:
	Controller();
	~Controller();
	
	void update();

	bool _key_pressable[];

	void handleKeyboardEvent(SDL_Event event);
	bool isPressed(SDL_Scancode keycode);
	bool isHold(SDL_Scancode keycode);
};

#endif