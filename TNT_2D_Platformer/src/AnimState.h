#pragma once
#ifndef __ANIM_STATES__
#define __ANIM_STATES__

enum AnimState {
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK,
	ASSAULTED,
	DEATH,
	ENEMY_PATROL,
	ENEMY_SEEK,
	ENEMY_ARRIVE,
	ATTACK_RANGED,
	NUM_OF_ANIM_STATES
};

#endif /* defined (__STEERING_STATE__) */