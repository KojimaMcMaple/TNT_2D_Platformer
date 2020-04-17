#include "Arrow.h"
#include "Game.h"

Arrow::Arrow(int x, int y, int direction)
{
	setTextureId("arrow");
	TheTextureManager::Instance()->load("../Assets/textures/Arrow.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc({ 0, 0, 16, 1 });
	setVelocityX(10);
	setDst({ x, y, 16, 1 });
	setMoveDirection(direction);
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	setDstX(getDstX() + getMoveDirection() * getVelocityX());
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
