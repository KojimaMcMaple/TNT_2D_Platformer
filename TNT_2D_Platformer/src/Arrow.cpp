#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(int x, int y, int direction)
{
	setTextureId("arrow");
	TheTextureManager::Instance()->load("../Assets/textures/Arrow.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc({ 0, 0, 16, 1 });
	SetWorldRect( x, y, 16 * 3, 1 * 3);
	setDst({ 0, 0, 16 * 3, 1 * 3 });
	SetCollidable(true);
	setVelocityX(10);	
	setMoveDirection(direction);
	setType(GameObjectType::ARROW);
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	SetWorldXAndHitBox(GetWorldRect()->x + getMoveDirection() * getVelocityX());
}

void Arrow::draw()
{
	switch (getMoveDirection()) {
	case -1:
		TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "arrow", getSrc(), getDst(), 0.0, 0, SDL_FLIP_HORIZONTAL);
		break;
	case 1:
		TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "arrow", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
		break;
	}	
}

void Arrow::clean()
{
}
