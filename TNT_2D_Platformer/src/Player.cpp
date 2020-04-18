#include "Player.h"
#include "Game.h"

Player::Player()
{
	setTextureId("player");
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-v1.5-Sheet.png", getTextureId(), TheGame::Instance()->getRenderer());

	// TO UPDATE TEXTURE PACK
	TheTextureManager::Instance()->load("../Assets/textures/adventurer-bow-Sheet.png", "attack_ranged", TheGame::Instance()->getRenderer());

	setSrc(0, 0, 50, 37);
	SetWorldRect(0, 0, 50 * 3, 37 * 3);
	setDst(0, 0, 50 * 3, 37 * 3);
	setHitBox(0, 0, 45, 85);
	//setHitBoxOffsetX(-4);
	//setHitBoxOffsetY(10);
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
	setMaxVelocityY(14.5);
	setDrag(0.9);
	setMoveDirection(1);
	setType(GameObjectType::PLAYER);
	setAnimState(AnimState::IDLE); //default anim state
	SetHP(100);
	SetAtkPower(20);

	// ANIM INIT
	InitAnimList();
	GetAnimList()[IDLE]->SetAnimId(IDLE);
	GetAnimList()[IDLE]->SetStartRow(0);
	GetAnimList()[IDLE]->SetStartCol(0);
	GetAnimList()[IDLE]->SetNumFrames(4);
	GetAnimList()[IDLE]->SetAnimSpeed(0.15f);
	GetAnimList()[IDLE]->SetLooping(true);
	GetAnimList()[IDLE]->SetMaxSheetRow(16); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetMaxSheetCol(7); //same for all anim states since there's only one sheet

	GetAnimList()[RUN]->SetAnimId(RUN);
	GetAnimList()[RUN]->SetStartRow(1);
	GetAnimList()[RUN]->SetStartCol(1);
	GetAnimList()[RUN]->SetNumFrames(6);
	GetAnimList()[RUN]->SetAnimSpeed(0.45f);
	GetAnimList()[RUN]->SetLooping(true);
	GetAnimList()[RUN]->SetMaxSheetRow(16); //same for all anim states since there's only one sheet
	GetAnimList()[RUN]->SetMaxSheetCol(7); //same for all anim states since there's only one sheet
	
	GetAnimList()[JUMP]->SetAnimId(JUMP);
	GetAnimList()[JUMP]->SetStartRow(2);
	GetAnimList()[JUMP]->SetStartCol(2);
	GetAnimList()[JUMP]->SetNumFrames(2);
	GetAnimList()[JUMP]->SetAnimSpeed(0.20f);
	GetAnimList()[JUMP]->SetLooping(false);
	GetAnimList()[JUMP]->SetMaxSheetRow(16); //same for all anim states since there's only one sheet
	GetAnimList()[JUMP]->SetMaxSheetCol(7); //same for all anim states since there's only one sheet

	GetAnimList()[FALL]->SetAnimId(FALL);
	GetAnimList()[FALL]->SetStartRow(3);
	GetAnimList()[FALL]->SetStartCol(1);
	GetAnimList()[FALL]->SetNumFrames(2);
	GetAnimList()[FALL]->SetAnimSpeed(0.20f);
	GetAnimList()[FALL]->SetLooping(true);
	GetAnimList()[FALL]->SetMaxSheetRow(16); //same for all anim states since there's only one sheet
	GetAnimList()[FALL]->SetMaxSheetCol(7); //same for all anim states since there's only one sheet

	GetAnimList()[ATTACK]->SetAnimId(ATTACK);
	GetAnimList()[ATTACK]->SetStartRow(6); //2nd attack in texture sheet
	GetAnimList()[ATTACK]->SetStartCol(5);
	GetAnimList()[ATTACK]->SetNumFrames(6);
	//GetAnimList()[ATTACK]->SetAnimSpeed(0.2f);
	GetAnimList()[ATTACK]->SetAnimSpeed(0.7f);
	GetAnimList()[ATTACK]->SetLooping(false);
	GetAnimList()[ATTACK]->SetMaxSheetRow(16); //same for all anim states since there's only one sheet
	GetAnimList()[ATTACK]->SetMaxSheetCol(7); //same for all anim states since there's only one sheet
	GetAnimList()[ATTACK]->SetAtkStartFrame(3);
	GetAnimList()[ATTACK]->SetAtkNumFrames(2);
	SetAtkHitBox(0, 0, 70, 85);

	GetAnimList()[ATTACK_RANGED]->SetAnimId(ATTACK_RANGED);
	GetAnimList()[ATTACK_RANGED]->SetStartRow(0); 
	GetAnimList()[ATTACK_RANGED]->SetStartCol(0);
	GetAnimList()[ATTACK_RANGED]->SetNumFrames(9);
	GetAnimList()[ATTACK_RANGED]->SetAnimSpeed(0.7f);
	GetAnimList()[ATTACK_RANGED]->SetLooping(false);
	GetAnimList()[ATTACK_RANGED]->SetMaxSheetRow(4); //same for all anim states since there's only one sheet
	GetAnimList()[ATTACK_RANGED]->SetMaxSheetCol(4); //same for all anim states since there's only one sheet

	// Player HUD
	m_statusBar = new StatusBar(getDst(), 100);
}

Player::~Player()
{
}

void Player::update()
{
	// UPDATE POSITION
	setAccelerationX(std::min(std::max(getAccelerationX(), -getMaxAccelerationX()), getMaxAccelerationX()));
	setVelocityX((getVelocityX() + getAccelerationX()) * getDrag());
	setVelocityX(std::min(std::max(getVelocityX(), -getMaxVelocityX()), getMaxVelocityX()));
	SetWorldXAndHitBox(GetWorldRect()->x + (int)getVelocityX());

	setVelocityY(getVelocityY() + getAccelerationY() + (getGravity()/5));
	setVelocityY(std::min(std::max(getVelocityY(), -getMaxVelocityY()*10), getMaxVelocityY()));
	SetWorldYAndHitBox(GetWorldRect()->y + (int)getVelocityY());

	// UPDATE PLAYER HUD
	m_statusBar->update(getDst());
}

void Player::draw()
{
	Animate();
	switch (getMoveDirection()) {
	case -1:
		// TO UPDATE TEXTURE PACK
		if (getAnimState() == ATTACK_RANGED)
		{
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "attack_ranged", getSrc(), getDst(), 0.0, 0, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_HORIZONTAL);
		}
		break;
	default:
		// TO UPDATE TEXTURE PACK
		if (getAnimState() == ATTACK_RANGED)
		{
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), "attack_ranged", getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
		}
		else
		{
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
		}
		break;
	}

	// Draw player HUD
	m_statusBar->draw();
}

void Player::clean()
{
	//delete m_statusBar;
	//m_statusBar = nullptr;
}

StatusBar* Player::getStatusBar()
{
	return m_statusBar;
}

void Player::MoveX()
{
	setAccelerationX(getAccelerationX() + 0.1 * getMoveDirection());
}

void Player::StopX()
{
	setAccelerationX(0);
	setVelocityX(0);
}