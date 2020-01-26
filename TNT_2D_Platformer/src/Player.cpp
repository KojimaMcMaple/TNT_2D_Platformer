#include "Player.h"
#include "Game.h"

Player::Player()
{
	setTextureId("player");
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-v1.5-Sheet.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 55, 37);
	setDst(0, 0, 55*3, 37*3);
	setCollideBox(0, 0, 55, 37);
	setIsColliding(true);
	setVelocity(10);
	setType(GameObjectType::PLAYER);

	/*TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);*/
}

Player::~Player()
{
}

void Player::update()
{
	/*glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	setPosition(glm::vec2(mouseVector.x, getPosition().y));*/

	
}

void Player::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "player", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void Player::clean()
{
	
}
