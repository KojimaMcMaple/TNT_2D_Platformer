#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "StatusBar.h"

class Player : public GameObject {
private:
	StatusBar* m_statusBar;
public:
	enum AnimState {
		IDLE,
		RUN,
		JUMP,
		FALL,
		ATTACK,
		ATTACK_RANGED,
		ASSAULTED,
		NUM_OF_ANIM_STATES
	};
	Player();
	~Player();
	void update() override;
	void draw() override;
	void clean() override;

	StatusBar* getStatusBar();

	void MoveX();
	void StopX();

	friend class Camera;
};


#endif /* defined (__Player__) */