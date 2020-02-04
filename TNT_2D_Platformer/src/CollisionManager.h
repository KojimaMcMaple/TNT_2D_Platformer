#pragma once
#ifndef __CollisionManager__
#define __CollisionManager__

// core libraries
#include <iostream>

#include "GameObject.h"
#include <GLM/gtx/norm.hpp>
#include "SoundManager.h"

class CollisionManager
{
public:
	static bool WillCollideAABB(SDL_Rect* obj1, SDL_Rect* obj2, int velocity);
	static bool WillCollideRight(SDL_Rect* obj1, SDL_Rect* obj2, int velocity);
	static bool WillCollideLeft(SDL_Rect* obj1, SDL_Rect* obj2, int velocity);
	static bool WillCollideTop(SDL_Rect* obj1, SDL_Rect* obj2, int velocity);
	static bool WillCollideDown(SDL_Rect* obj1, SDL_Rect* obj2, int velocity);
	static bool HaveCollidedAABB(SDL_Rect* obj1, SDL_Rect* obj2);
	static int squaredDistance(glm::vec2 P1, glm::vec2 P2);
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);
private:
	CollisionManager();
	~CollisionManager();
};

typedef CollisionManager Collision;

#endif /* defined (__CollisionManager__) */
