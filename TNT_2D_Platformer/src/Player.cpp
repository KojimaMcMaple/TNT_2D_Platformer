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
	setType(GameObjectType::PLAYER);

	/*TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);*/

	// CHEAT CODES
	//setCustomPivotX(25*3);
	//setCustomPivotY(20*3);
}


void Player::update()
{
	setHitBoxX(getDstCenterX() - getHitBoxW() / 2 + getHitBoxOffsetX());
	setHitBoxY(getDstCenterY() - getHitBoxH() / 2 + getHitBoxOffsetY());
	
	/*glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	setPosition(glm::vec2(mouseVector.x, getPosition().y));*/
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
