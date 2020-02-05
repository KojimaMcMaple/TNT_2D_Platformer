#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(SDL_Renderer* renderer)
{
	setTextureId("player");
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-v1.5-Sheet.png", getTextureId(), renderer);
	setSrc(0, 0, 55, 37);
	setDst(0, 0, 55 * 3, 37 * 3);
	setHitBox(0, 0, 50, 85);
	setHitBoxOffsetX(-8);
	setHitBoxOffsetY(10);
	//setHitBoxVisibility(true); //set this in GameObject.h to toggle collide boxes for ALL objects
	setIsColliding(true);
	setGrounded(false);
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

void Player::MoveX() 
{
	setAccelerationX(getAccelerationX() + 0.1 * getMoveDirection());
}

void Player::update()
{
	setAccelerationX(std::min(std::max(getAccelerationX(), -getMaxAccelerationX()), getMaxAccelerationX()));
	setVelocityX((getVelocityX() + getAccelerationX()) * getDrag());
	setVelocityX(std::min(std::max(getVelocityX(), -getMaxVelocityX()), getMaxVelocityX()));
	//setDstX(getDstX() + (int)getVelocityX());

	setVelocityY(getVelocityY() + getAccelerationY() + (getGravity() / 3));
	setVelocityY(std::min(std::max(getVelocityY(), -getMaxVelocityY() * 3), getMaxVelocityY()));
	//std::cout << "getVelocityY = " << getVelocityY() << std::endl;
	//std::cout << "-1*getMaxVelocityY()*10 = " << -1 * getMaxVelocityY() * 10 << std::endl;
	//std::cout << "getMaxVelocityY = " << getMaxVelocityY() << std::endl;
	//std::cout << "std::max(getVelocityY(), -1*getMaxVelocityY()*10) = " << std::max(getVelocityY(), -1 * getMaxVelocityY() * 10) << std::endl;
	
	//setDstY(getDstY() + (int)getVelocityY());
	
	//setHitBoxX(getDstCenterX() - getHitBoxW() / 2 + getHitBoxOffsetX());
	//setHitBoxY(getDstCenterY() - getHitBoxH() / 2 + getHitBoxOffsetY());
}

void Player::draw()
{
}

void Player::draw(SDL_Renderer* renderer)
{
	TheTextureManager::Instance()->draw(renderer, "player", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
	if (isHitBoxVisible()) {
		/*SDL_SetRenderDrawColor(renderer, 150, 0, 0, 50);
		SDL_Rect temp_rect = { getDstX(),getDstY(),getDstW(),getDstH() };
		SDL_RenderFillRect(renderer, &temp_rect);*/
		SDL_SetRenderDrawColor(renderer, 0, 150, 0, 50);
		SDL_RenderFillRect(renderer, getHitBox());
	}
}

void Player::clean()
{
	
}
