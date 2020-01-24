#include "Player.h"
#include "Game.h"

Player::Player()
{
	setTextureId("player");
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-v1.5-Sheet.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 55, 37);
	setDst(0, 0, 55*3, 37*3);
	setCollideBox(0, 0, 55, 37);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);

	/*TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);*/
}

Player::~Player()
{
}

void Player::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "player", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void Player::update()
{
	/*glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();
	setPosition(glm::vec2(mouseVector.x, getPosition().y));*/

	// PROCESSING, HAPPENS WHEN KEYS ARE HELD DOWN
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_W) || TheGame::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		
	}
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_S) || TheGame::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		
	}
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_A) || TheGame::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		
	}
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_D) || TheGame::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		
	}
}

void Player::clean()
{
	
}
