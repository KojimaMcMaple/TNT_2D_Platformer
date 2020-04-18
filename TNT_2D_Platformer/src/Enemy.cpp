#include "Enemy.h"
#include "Game.h"

void Enemy::InitSkeletonSword(int world_x, int world_y)
{
	enemy_type_ = SKELETON_SWORD;
	
	setTextureId("skeleton_sword");
	TheTextureManager::Instance()->load("../Assets/textures/skeleton_sword.png", getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(0, 0, 80, 48);
	SetWorldRect(0, 0, getSrc()->w * 3, getSrc()->h * 3);
	setDst(0, 0, GetWorldRect()->w, GetWorldRect()->h);
	setHitBox(0, 0, 45, 85);
	SetSpawnPointX(world_x);
	SetSpawnPointY(world_y);
	SetWorldXAndHitBox(world_x);
	SetWorldYAndHitBox(world_y);
	SetPatrolRadius(300);
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
	setMaxAccelerationX(4.0);
	setMaxAccelerationY(2.0);
	setMaxVelocityX(0.0); //not used
	setMaxVelocityY(10.0);
	setDrag(1.0);
	setMoveDirection(-1);
	setType(GameObjectType::ENEMY);
	setAnimState(AnimState::ENEMY_PATROL);
	SetMaxHP(40);
	SetHP(GetMaxHP());
	SetAtkPower(20);
	SetSightRect(world_x, world_y, 200, 150);

	// ANIM INIT
	InitAnimList();
	GetAnimList()[ENEMY_PATROL]->SetAnimId(ENEMY_PATROL);
	GetAnimList()[ENEMY_PATROL]->SetStartRow(7);
	GetAnimList()[ENEMY_PATROL]->SetStartCol(4);
	GetAnimList()[ENEMY_PATROL]->SetNumFrames(6);
	GetAnimList()[ENEMY_PATROL]->SetAnimSpeed(0.2f);
	GetAnimList()[ENEMY_PATROL]->SetLooping(true);
	GetAnimList()[ENEMY_PATROL]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ENEMY_PATROL]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[ASSAULTED]->SetAnimId(ASSAULTED);
	GetAnimList()[ASSAULTED]->SetStartRow(4);
	GetAnimList()[ASSAULTED]->SetStartCol(2);
	GetAnimList()[ASSAULTED]->SetNumFrames(3);
	SetIFrames(3); //NOT YET IMPLEMENTED, IS USING SIMPLER SOLUTION
	GetAnimList()[ASSAULTED]->SetAnimSpeed(0.3f);
	GetAnimList()[ASSAULTED]->SetLooping(false);
	GetAnimList()[ASSAULTED]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ASSAULTED]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[DEATH]->SetAnimId(DEATH);
	GetAnimList()[DEATH]->SetStartRow(3);
	GetAnimList()[DEATH]->SetStartCol(2);
	GetAnimList()[DEATH]->SetNumFrames(6);
	GetAnimList()[DEATH]->SetAnimSpeed(0.5f);
	GetAnimList()[DEATH]->SetLooping(false);
	GetAnimList()[DEATH]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[DEATH]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[ENEMY_SEEK]->SetAnimId(ENEMY_SEEK);
	GetAnimList()[ENEMY_SEEK]->SetStartRow(6);
	GetAnimList()[ENEMY_SEEK]->SetStartCol(4);
	GetAnimList()[ENEMY_SEEK]->SetNumFrames(6);
	GetAnimList()[ENEMY_SEEK]->SetAnimSpeed(0.6f);
	GetAnimList()[ENEMY_SEEK]->SetLooping(true);
	GetAnimList()[ENEMY_SEEK]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ENEMY_SEEK]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[ENEMY_FLEE]->SetAnimId(ENEMY_FLEE);
	GetAnimList()[ENEMY_FLEE]->SetStartRow(6);
	GetAnimList()[ENEMY_FLEE]->SetStartCol(4);
	GetAnimList()[ENEMY_FLEE]->SetNumFrames(6);
	GetAnimList()[ENEMY_FLEE]->SetAnimSpeed(0.6f);
	GetAnimList()[ENEMY_FLEE]->SetLooping(true);
	GetAnimList()[ENEMY_FLEE]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ENEMY_FLEE]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[ENEMY_ARRIVE]->SetAnimId(ENEMY_ARRIVE);
	GetAnimList()[ENEMY_ARRIVE]->SetStartRow(5);
	GetAnimList()[ENEMY_ARRIVE]->SetStartCol(4);
	GetAnimList()[ENEMY_ARRIVE]->SetNumFrames(3);
	GetAnimList()[ENEMY_ARRIVE]->SetAnimSpeed(0.3f);
	GetAnimList()[ENEMY_ARRIVE]->SetLooping(true);
	GetAnimList()[ENEMY_ARRIVE]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ENEMY_ARRIVE]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet

	GetAnimList()[ATTACK]->SetAnimId(ATTACK);
	GetAnimList()[ATTACK]->SetStartRow(1);
	GetAnimList()[ATTACK]->SetStartCol(0);
	GetAnimList()[ATTACK]->SetNumFrames(6);
	GetAnimList()[ATTACK]->SetAnimSpeed(0.5f);
	GetAnimList()[ATTACK]->SetLooping(false);
	GetAnimList()[ATTACK]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ATTACK]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet'
	GetAnimList()[ATTACK]->SetAtkStartFrame(3);
	GetAnimList()[ATTACK]->SetAtkNumFrames(2);
	SetAtkHitBox(0, 0, 85, 85);
}

void Enemy::RenderSkeletonSword()
{
	
}

Enemy::Enemy()
{
}

Enemy::Enemy(EnemyType type, int world_x, int world_y)
{
	switch (type) {
	case SKELETON_SWORD:
		InitSkeletonSword(world_x, world_y);
		break;
	}
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
	switch (enemy_type_) {
	default:
		int strike_distance = GetAtkHitBox()->w;
		int lose_sight_distance = getHitBox()->h * 3;

		// STATE UPDATE
		switch (getAnimState()) {
		case ENEMY_PATROL:
			// continue moving if not past patrol distance, else change direction
			if (IsGrounded()) {
				if (getMoveDirection()==1) { // MOVE RIGHT
					if (GetWorldRectRightmostX() + getVelocityX() > GetPatrolMaxX()) {
						setMoveDirection(-1);
					}
				}
				else { // MOVE LEFT
					if (GetWorldRect()->x + getVelocityX() < GetPatrolMinX()) {
						setMoveDirection(1);
					}
				}
				setAccelerationX(2.0);
				MoveX();
			}
			UpdatePosition();
			break;

		case ENEMY_SEEK:
			// continue moving if not past patrol distance, else change direction
			if (IsGrounded()) {
				if (target_x_ < GetWorldRectCenterX()) {
					setMoveDirection(-1);
				}
				else {
					setMoveDirection(1);
				}
				setAccelerationX(3.0);
				MoveX();
			}
			UpdatePosition();
			//if target within strike distance
			if (target_x_ > GetWorldRectCenterX() - strike_distance && target_x_ < GetWorldRectCenterX() + strike_distance) {
				setAnimState(AnimState::ENEMY_ARRIVE);
			}
			//if target gets too far away
			if (target_y_ < GetWorldRectCenterY() - lose_sight_distance || target_y_ > GetWorldRectCenterY() + lose_sight_distance) {
				setAnimState(AnimState::ENEMY_PATROL);
			}
			break;
			
		case ENEMY_FLEE:
			// continue moving if not past patrol distance, else change direction
			if (IsGrounded()) {
				if (target_x_ < GetWorldRectCenterX()) {
					setMoveDirection(1);
				}
				else {
					setMoveDirection(-1);
				}
				setAccelerationX(2.50);
				MoveX();
			}
			UpdatePosition();
			//if target gets too far away
			if (target_y_ < GetWorldRectCenterY() - lose_sight_distance || target_y_ > GetWorldRectCenterY() + lose_sight_distance) {
				setAnimState(AnimState::ENEMY_PATROL);
			}
			break;

		case ENEMY_ARRIVE:
			StopX();
			if (HasEndedAnimation()) {
				setAnimState(AnimState::ATTACK);
			}
			//if target within strike distance
			if (target_x_ < GetWorldRectCenterX() - strike_distance || target_x_ > GetWorldRectCenterX() + strike_distance) {
				setAnimState(AnimState::ENEMY_SEEK);
			}
			//if target gets too far away
			if (target_y_ < GetWorldRectCenterY() - lose_sight_distance || target_y_ > GetWorldRectCenterY() + lose_sight_distance) {
				setAnimState(AnimState::ENEMY_PATROL);
			}
			break;

		case ATTACK:
			StopX();
			if (IsAtkHitBoxActive()) {
				if (getMoveDirection() == 1) { //facing right
					SetAtkHitBoxX(getHitBoxRightmostX());
					SetAtkHitBoxY(getHitBoxY());
				}
				else { //facing left
					SetAtkHitBoxX(getHitBoxX() - GetAtkHitBox()->w);
					SetAtkHitBoxY(getHitBoxY());
				}
			}
			if (HasEndedAnimation()) {
				setAnimState(AnimState::ENEMY_ARRIVE);
			}
			break;

		case ASSAULTED:
			StopX();
			if (HasEndedAnimation()) {
				if (GetHP() == 0) {
					setAnimState(AnimState::DEATH);
				}
				// HP<50%, FLEE
				else if (GetHP() <= GetMaxHP() / 2) {
					setAnimState(AnimState::ENEMY_FLEE);
				}
				else {
					setAnimState(AnimState::ENEMY_PATROL);
				}
			}
			break;

		case DEATH:
			StopX();
			break;
		}
		
		// FORCE ATK HIT BOX TO TURN OFF
		if (getAnimState() != AnimState::ATTACK) {
			SetAtkHitBoxActive(false);
		}

		break;
	}
}

void Enemy::draw()
{
	switch (enemy_type_) {
	default:
		Animate();
		switch (getMoveDirection()) {
		case -1:
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_HORIZONTAL);
			break;
		default:
			TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
			break;
		}
		break;
	}
}

void Enemy::clean()
{
}

void Enemy::MoveX()
{
	//setAccelerationX(getAccelerationX() + 0.1 * getMoveDirection());
	setVelocityX(getAccelerationX() * getMoveDirection());
}

void Enemy::StopX()
{
	setAccelerationX(0);
	setVelocityX(0);
}

void Enemy::UpdatePosition()
{
	// UPDATE POSITION
	//setAccelerationX(std::min(std::max(getAccelerationX(), -getMaxAccelerationX()), getMaxAccelerationX()));
	//setVelocityX((getVelocityX() + getAccelerationX()) * getDrag());
	//setVelocityX(std::min(std::max(getVelocityX(), -getMaxVelocityX()), getMaxVelocityX()));
	SetWorldXAndHitBox(GetWorldRect()->x + (int)getVelocityX());

	setVelocityY(getVelocityY() + getAccelerationY() + (getGravity() / 5));
	setVelocityY(std::min(std::max(getVelocityY(), -getMaxVelocityY() * 10), getMaxVelocityY()));
	SetWorldYAndHitBox(GetWorldRect()->y + (int)getVelocityY());

	// UPDATE SIGHT RECT
	if (getMoveDirection() == 1) { // MOVE RIGHT
		SetSightRectX(getHitBoxCenterX());
		SetSightRectY(getHitBoxCenterY() - GetSightRect()->h / 2);
	}
	else { // MOVE LEFT
		SetSightRectX(getHitBoxCenterX() - GetSightRect()->w);
		SetSightRectY(getHitBoxCenterY() - GetSightRect()->h / 2);
	}
}

int Enemy::GetSpawnPointX()
{
	return spawn_point_x_;
}

int Enemy::GetSpawnPointY()
{
	return spawn_point_y_;
}

int Enemy::GetPatrolRadius()
{
	return patrol_radius_;
}

int Enemy::GetPatrolMinX()
{
	return (spawn_point_x_ - patrol_radius_);
}

int Enemy::GetPatrolMaxX()
{
	return (spawn_point_x_ + patrol_radius_);
}

int Enemy::GetTargetX()
{
	return target_x_;
}

int Enemy::GetTargetY()
{
	return target_y_;
}

void Enemy::SetSpawnPointX(int value)
{
	spawn_point_x_ = value;
}

void Enemy::SetSpawnPointY(int value)
{
	spawn_point_y_ = value;
}

void Enemy::SetPatrolRadius(int value)
{
	patrol_radius_ = value;
}

void Enemy::SetTarget(int x, int y)
{
	target_x_ = x;
	target_y_ = y;
}
