#include "Player.h"
#include "Game.h"

Player::Player()
{
	setTextureId("player");
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-v1.5-Sheet.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 50, 37);
	SetWorldRect(0, 0, 50 * 3, 37 * 3);
	setDst(0, 0, 50 * 3, 37 * 3);
	setHitBox(0, 0, 45, 85);
	setHitBoxOffsetX(-8);
	setHitBoxOffsetY(10);
	//SetHitBoxVisibility(true); //set this in GameObject.h to toggle collide boxes for ALL objects
	SetCollidable(true);
	SetGrounded(false);
	setAccelerationX(0);
	setAccelerationY(0);
	setVelocityX(0);
	setVelocityY(0);
	setGravity(Globals::sGravity);
	setMaxAccelerationX(2.0);
	setMaxAccelerationY(2.0);
	setMaxVelocityX(6.0);
	setMaxVelocityY(getGravity());
	setDrag(0.9);
	setMoveDirection(1);
	setType(GameObjectType::PLAYER);

	/*TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);*/
}

Player::~Player()
{
}

void Player::MoveX() 
{
	setAccelerationX(getAccelerationX() + 0.1 * getMoveDirection());
}

void Player::update()
{
	// UPDATE POSITION
	setAccelerationX(std::min(std::max(getAccelerationX(), -getMaxAccelerationX()), getMaxAccelerationX()));
	setVelocityX((getVelocityX() + getAccelerationX()) * getDrag());
	setVelocityX(std::min(std::max(getVelocityX(), -getMaxVelocityX()), getMaxVelocityX()));
	SetWorldRectX(GetWorldRect()->x + (int)getVelocityX());
	//std::cout << "getVelocityX = " << getVelocityX() << std::endl;

	setVelocityY(getVelocityY() + getAccelerationY() + (getGravity() / 3));
	setVelocityY(std::min(std::max(getVelocityY(), -getMaxVelocityY() * 3), getMaxVelocityY()));
	SetWorldRectY(GetWorldRect()->y + (int)getVelocityY());
	//std::cout << "getVelocityY = " << getVelocityY() << std::endl;
	
	// UPDATE HITBOX
	setHitBoxX(GetWorldRectCenterX() - getHitBoxW() / 2 + getHitBoxOffsetX());
	setHitBoxY(GetWorldRectCenterY() - getHitBoxH() / 2 + getHitBoxOffsetY());
}

void Player::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void Player::clean()
{
	
}
