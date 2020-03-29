#pragma once
#ifndef __Camera__
#define __Camera__

#include "Globals.h"
#include "GameObject.h"
#include "Player.h"
#include "Level.h"

class Camera : public GameObject {	
public:
	Camera();
	~Camera();

	void update() override;
	void draw() override;
	void draw(GameObject* obj_ptr);
	void clean() override;

	void RefocusCamera(Player* player_ptr, Level* level_ptr);
};

#endif