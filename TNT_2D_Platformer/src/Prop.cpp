#include "Prop.h"
#include "Game.h"

void Prop::InitBarrel(int world_x, int world_y)
{
	prop_type_ = BARREL;

	setTextureId("BARREL");
	TheTextureManager::Instance()->load("../Assets/textures/Barrel_0.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 160, 60);
	SetWorldRect(0, 0, getSrc()->w, getSrc()->h);
	setDst(0, 0, GetWorldRect()->w, GetWorldRect()->h);
	setHitBox(0, 0, 48, 60);
	SetWorldXAndHitBox(world_x);
	SetWorldYAndHitBox(world_y);
	//setHitBoxOffsetX(-4);
	//setHitBoxOffsetY(10);
	//SetHitBoxVisibility(true); //set this in GameObject.h to toggle collide boxes for ALL objects
	SetCollidable(true);
	SetGrounded(false);
	setType(GameObjectType::PROP);
	setAnimState(AnimState::IDLE);
	SetMaxHP(40);
	SetHP(GetMaxHP());

	// ANIM INIT
	InitAnimList(NUM_OF_ANIM_STATES);
	GetAnimList()[IDLE]->SetAnimId(IDLE);
	GetAnimList()[IDLE]->SetStartRow(0);
	GetAnimList()[IDLE]->SetStartCol(0);
	GetAnimList()[IDLE]->SetNumFrames(1);
	GetAnimList()[IDLE]->SetAnimSpeed(0.0f);
	GetAnimList()[IDLE]->SetLooping(false);
	GetAnimList()[IDLE]->SetMaxSheetRow(1); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetMaxSheetCol(3); //same for all anim states since there's only one sheet

	GetAnimList()[ASSAULTED]->SetAnimId(ASSAULTED);
	GetAnimList()[ASSAULTED]->SetStartRow(0);
	GetAnimList()[ASSAULTED]->SetStartCol(1);
	GetAnimList()[ASSAULTED]->SetNumFrames(1);
	GetAnimList()[ASSAULTED]->SetAnimSpeed(0.0f);
	GetAnimList()[ASSAULTED]->SetLooping(false);
	GetAnimList()[ASSAULTED]->SetMaxSheetRow(1); //same for all anim states since there's only one sheet
	GetAnimList()[ASSAULTED]->SetMaxSheetCol(3); //same for all anim states since there's only one sheet

	GetAnimList()[DEATH]->SetAnimId(DEATH);
	GetAnimList()[DEATH]->SetStartRow(0);
	GetAnimList()[DEATH]->SetStartCol(2);
	GetAnimList()[DEATH]->SetNumFrames(1);
	GetAnimList()[DEATH]->SetAnimSpeed(0.0f);
	GetAnimList()[DEATH]->SetLooping(false);
	GetAnimList()[DEATH]->SetMaxSheetRow(1); //same for all anim states since there's only one sheet
	GetAnimList()[DEATH]->SetMaxSheetCol(3); //same for all anim states since there's only one sheet
}

void Prop::UpdateBarrel()
{
	if (GetHP() == 0) {
		setAnimState(DEATH);
	}
	else if (GetHP() <= GetMaxHP()/2) {
		setAnimState(ASSAULTED);
	}
}

void Prop::RenderBarrel()
{
	Animate();
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

Prop::Prop()
{
}

Prop::Prop(PropType type, int world_x, int world_y)
{
	switch (type) {
	case BARREL:
		InitBarrel(world_x, world_y);
		break;
	}
}

Prop::~Prop()
{
}

void Prop::update()
{
	switch (prop_type_) {
	case BARREL:
		UpdateBarrel();
		break;
	}
}

void Prop::draw()
{
	switch (prop_type_) {
	case BARREL:
		RenderBarrel();
		break;
	}
}

void Prop::clean()
{
}
