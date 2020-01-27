#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Player : public GameObject {
private:

public:
	Player();
	~Player();
	Player(SDL_Renderer* renderer);

	void update() override;
	void draw() override;
	void draw(SDL_Renderer* renderer);
	void clean() override;
};


#endif /* defined (__Player__) */