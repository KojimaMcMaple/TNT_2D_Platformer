#pragma once
#ifndef __PROP__
#define __PROP__

#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "TextureManager.h"
#include "PropType.h"

class Prop : public GameObject {
private:
	PropType prop_type_;

	void InitBarrel(int world_x = 0, int world_y = 0);
	void UpdateBarrel();
	void RenderBarrel();
public:
	enum AnimState {
		IDLE,
		ASSAULTED,
		DEATH,
		NUM_OF_ANIM_STATES
	};
	Prop();
	Prop(PropType type, int world_x, int world_y);
	~Prop();

	void update() override;
	void draw() override;
	void clean() override;

	PropType GetPropType();

	friend class Camera;
};


#endif /* defined (__Player__) */