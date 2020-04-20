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
	setAnimState(AnimState::IDLE);
	SetMaxHP(40);
	SetHP(GetMaxHP());
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

void Prop::RenderBarrel()
{
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

PropType Prop::GetPropType()
{
	return prop_type_;
}
