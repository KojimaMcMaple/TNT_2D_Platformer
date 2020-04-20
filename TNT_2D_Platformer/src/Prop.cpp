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
	setHitBox(0, 0, 48, 40);
	SetWorldXAndHitBox(world_x);
	SetWorldYAndHitBox(world_y);
	SetCollidable(true);
	SetGrounded(false);
	setVelocityY(2);
	setType(GameObjectType::PROP);
	SetMaxHP(40);
	SetHP(GetMaxHP());
}

void Prop::InitSpikeTrap(int world_x, int world_y)
{
	prop_type_ = SPIKE_TRAP;

	setTextureId("SPIKE_TRAP");
	TheTextureManager::Instance()->load("../Assets/textures/Spike_Trap.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 32, 32);
	SetWorldRect(0, 0, getSrc()->w*2, getSrc()->h*2);
	setDst(0, 0, GetWorldRect()->w, GetWorldRect()->h);
	setHitBox(0, 0, 45, 1);
	setHitBoxOffsetY(-20);
	SetWorldXAndHitBox(world_x);
	SetWorldYAndHitBox(world_y);
	SetCollidable(true);
	SetGrounded(false);
	setVelocityY(2);
	setType(GameObjectType::PROP);
	setAnimState(AnimState::IDLE);
	SetMaxHP(100);
	SetHP(GetMaxHP());
	SetAtkPower(10);

	// ANIM INIT
	InitAnimList(NUM_OF_ANIM_STATES);
	GetAnimList()[IDLE]->SetAnimId(IDLE);
	GetAnimList()[IDLE]->SetStartRow(0);
	GetAnimList()[IDLE]->SetStartCol(0);
	GetAnimList()[IDLE]->SetNumFrames(14);
	GetAnimList()[IDLE]->SetAnimSpeed(1.0f);
	GetAnimList()[IDLE]->SetLooping(true);
	GetAnimList()[IDLE]->SetMaxSheetRow(1); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetMaxSheetCol(14); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetAtkStartFrame(8);
	GetAnimList()[IDLE]->SetAtkNumFrames(4);
	SetAtkHitBox(0, 0, 50, 20);
}

void Prop::InitFireTrap(int world_x, int world_y)
{
	prop_type_ = FIRE_TRAP;

	setTextureId("FIRE_TRAP");
	TheTextureManager::Instance()->load("../Assets/textures/Fire_Trap.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 32, 41);
	SetWorldRect(0, 0, getSrc()->w*2, getSrc()->h*2);
	setDst(0, 0, GetWorldRect()->w, GetWorldRect()->h);
	setHitBox(0, 0, 30, 1);
	setHitBoxOffsetY(0);
	SetWorldXAndHitBox(world_x);
	SetWorldYAndHitBox(world_y);
	SetCollidable(true);
	SetGrounded(false);
	setVelocityY(2);
	setType(GameObjectType::PROP);
	setAnimState(AnimState::IDLE);
	SetMaxHP(100);
	SetHP(GetMaxHP());
	SetAtkPower(10);

	// ANIM INIT
	InitAnimList(NUM_OF_ANIM_STATES);
	GetAnimList()[IDLE]->SetAnimId(IDLE);
	GetAnimList()[IDLE]->SetStartRow(0);
	GetAnimList()[IDLE]->SetStartCol(0);
	GetAnimList()[IDLE]->SetNumFrames(14);
	GetAnimList()[IDLE]->SetAnimSpeed(1.0f);
	GetAnimList()[IDLE]->SetLooping(true);
	GetAnimList()[IDLE]->SetMaxSheetRow(1); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetMaxSheetCol(14); //same for all anim states since there's only one sheet
	GetAnimList()[IDLE]->SetAtkStartFrame(8);
	GetAnimList()[IDLE]->SetAtkNumFrames(2);
	SetAtkHitBox(0, 0, 50, 50);
}

void Prop::UpdateBarrel()
{
	// SET STATE
	if (GetHP() == 0) {
		setSrcX(2 * getSrc()->w);
	}
	else if (GetHP() <= GetMaxHP()/2) {
		setSrcX(1 * getSrc()->w);
	}

	// GRAVITY
	SetWorldYAndHitBox(GetWorldRect()->y + (int)getVelocityY());
}

void Prop::UpdateSpikeTrap()
{
	if (IsAtkHitBoxActive()) {
		SetAtkHitBoxX(getHitBoxCenterX() - GetAtkHitBox()->w / 2);
		SetAtkHitBoxY(getHitBoxY() - GetAtkHitBox()->h);
	}
	
	// GRAVITY
	SetWorldYAndHitBox(GetWorldRect()->y + (int)getVelocityY());
}

void Prop::RenderBarrel()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void Prop::RenderSpikeTrap()
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
	case SPIKE_TRAP:
		InitSpikeTrap(world_x, world_y);
		break;
	case FIRE_TRAP:
		InitFireTrap(world_x, world_y);
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
	case SPIKE_TRAP:
		UpdateSpikeTrap();
		break;
	case FIRE_TRAP:
		UpdateSpikeTrap();
		break;
	}

}

void Prop::draw()
{
	switch (prop_type_) {
	case BARREL:
		RenderBarrel();
		break;
	case SPIKE_TRAP:
		RenderSpikeTrap();
		break;
	case FIRE_TRAP:
		RenderSpikeTrap();
		break;
	}
}

void Prop::clean()
{
}

PropType Prop::GetPropType()
{
	return prop_type_;
}
