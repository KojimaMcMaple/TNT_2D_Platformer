#pragma once
#include "SDL.h"

class StatusBar
{
private:
	SDL_Rect m_Dst;
	int m_health, m_maxHealth;
public:
	StatusBar(SDL_Rect* hostDst, int maxHealth);
	void update(SDL_Rect* hostDst);
	void draw();

	// Pass negative value to take damage, otherwise to heal
	void changeHealth(int change);
	void SetHealth(int value);
};

