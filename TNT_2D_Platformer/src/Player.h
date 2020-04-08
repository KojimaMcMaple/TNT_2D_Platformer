#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Player : public GameObject {
private:

public:
	Player();
	~Player();
	
	void MoveX();
	void update() override;
	void draw() override;
	void clean() override;

	friend class Camera;
};


#endif /* defined (__Player__) */