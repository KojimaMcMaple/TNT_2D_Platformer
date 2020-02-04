#include "CollisionManager.h"

bool CollisionManager::WillCollideAABB(SDL_Rect* obj1, SDL_Rect* obj2, int velocity)
{
	if (obj1->x + obj1->w + velocity < obj2->x) {
		return false;
	}
	if (obj1->x + velocity > obj2->x + obj2->w) {
		return false;
	}
	if (obj1->y + obj1->h + velocity < obj2->y) {
		return false;
	}
	if (obj1->y + velocity > obj2->y + obj2->h) {
		return false;
	}
	return true;
}

bool CollisionManager::WillCollideRight(SDL_Rect* obj1, SDL_Rect* obj2, int velocity)
{
	if (!WillCollideAABB(obj1, obj2, velocity)) {
		return false;
	}
	if (obj1->x + obj1->w + velocity < obj2->x) {
		return false;
	}
	return true;
}

bool CollisionManager::WillCollideLeft(SDL_Rect* obj1, SDL_Rect* obj2, int velocity)
{
	if (!WillCollideAABB(obj1, obj2, velocity)) {
		return false;
	}
	if (obj1->x + velocity > obj2->x + obj2->w) {
		return false;
	}
	return true;
}

bool CollisionManager::WillCollideTop(SDL_Rect* obj1, SDL_Rect* obj2, int velocity)
{
	if (!WillCollideAABB(obj1, obj2, velocity)) {
		return false;
	}
	if (obj1->y + obj1->h + velocity < obj2->y) {
		return false;
	}
	return true;
}

bool CollisionManager::WillCollideDown(SDL_Rect* obj1, SDL_Rect* obj2, int velocity)
{
	if (!WillCollideAABB(obj1, obj2, velocity)) {
		return false;
	}
	if (obj1->y + velocity > obj2->y + obj2->h) {
		return false;
	}
	return true;
}

bool CollisionManager::HaveCollidedAABB(SDL_Rect* obj1, SDL_Rect* obj2)
{
	// alternatively, use SDL_HasIntersection
	//if (SDL_HasIntersection(obj1, obj2)) {
	//	return true;
	//}
	//else {
	//	return false;
	//}
	if (obj1->x + obj1->w < obj2->x) {
		return false;
	}
	if (obj1->x > obj2->x + obj2->w) {
		return false;
	}
	if (obj1->y + obj1->h < obj2->y) {
		return false;
	}
	if (obj1->y > obj2->y + obj2->h) {
		return false;
	}
	return true;
}

int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {
			
			object2->setIsColliding(true);

			switch (object2->getType()) {
			case ENEMY:
				break;
			default:
				std::cout << "Collision with unknown type!" << std::endl;
					break;
			}

			return true;
		}
		return false;
	}

	
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
