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
	setCollideBox(0, 0, 55, 37);
	setIsColliding(true);
	setType(GameObjectType::PLAYER);

	/*TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);*/
}


void Player::update()
{
	/*glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	setPosition(glm::vec2(mouseVector.x, getPosition().y));*/

	
}

void Player::draw()
{
}

void Player::draw(SDL_Renderer* renderer)
{
	TheTextureManager::Instance()->draw(renderer, "player", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void Player::clean()
{
	
}
