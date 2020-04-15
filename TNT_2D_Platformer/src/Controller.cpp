#include "Controller.h"

const Uint8* Controller::_key_state = SDL_GetKeyboardState(nullptr);

Controller::Controller()
{
	// For not repeating key
	this->_key_pressable[SDL_SCANCODE_LEFT]		= true;
	this->_key_pressable[SDL_SCANCODE_RIGHT]	= true;
	this->_key_pressable[SDL_SCANCODE_UP]		= true;
	this->_key_pressable[SDL_SCANCODE_DOWN]		= true;
	this->_key_pressable[SDL_SCANCODE_RSHIFT]	= true;
	this->_key_pressable[SDL_SCANCODE_ESCAPE]	= true;
	this->_key_pressable[SDL_SCANCODE_RETURN]	= true;
	this->_key_pressable[SDL_SCANCODE_SPACE]	= true;

}

Controller::~Controller()
{
}

void Controller::handleKeyboardEvent(SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		this->_key_pressable[event.key.keysym.scancode] = true;
	}
}

bool Controller::isPressed(SDL_Scancode keycode)
{
	bool _result = false;

	if (this->_key_state[keycode] && this->_key_pressable[keycode]) {
		this->_key_pressable[keycode] = false;
		_result = true;
	}
	return _result;
}

bool Controller::isHold(SDL_Scancode keycode)
{
	return this->_key_state[keycode];
}
