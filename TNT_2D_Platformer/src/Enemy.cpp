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
	SetLineOfSight(50);
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
	setMaxAccelerationX(2.0);
	setMaxAccelerationY(2.0);
	setMaxVelocityX(1.0);
	setMaxVelocityY(10.0);
	setDrag(1.0);
	setMoveDirection(-1);
	setType(GameObjectType::ENEMY);
	setAnimState(AnimState::ENEMY_PATROL);

	// ANIM INIT
	InitAnimList();
	GetAnimList()[ENEMY_PATROL]->SetAnimId(ENEMY_PATROL);
	GetAnimList()[ENEMY_PATROL]->SetStartRow(7);
	GetAnimList()[ENEMY_PATROL]->SetStartCol(4);
	GetAnimList()[ENEMY_PATROL]->SetNumFrames(6);
	GetAnimList()[ENEMY_PATROL]->SetAnimSpeed(0.15f);
	GetAnimList()[ENEMY_PATROL]->SetLooping(true);
	GetAnimList()[ENEMY_PATROL]->SetMaxSheetRow(9); //same for all anim states since there's only one sheet
	GetAnimList()[ENEMY_PATROL]->SetMaxSheetCol(6); //same for all anim states since there's only one sheet
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
		switch (getAnimState()) {
		case ENEMY_PATROL:
			// continue moving if not past patrol distance, else change direction
			if (IsGrounded()) {
				std::cout << "GetWorldRect()->x " << GetWorldRect()->x << std::endl;
				std::cout << "getMoveDirection() " << getMoveDirection() << std::endl;
				std::cout << "GetPatrolMaxX() " << GetPatrolMaxX() << std::endl;
				std::cout << "GetPatrolMinX() " << GetPatrolMinX() << std::endl;

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
				MoveX();
			}
			
			UpdatePosition();
			break;
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
	setVelocityX(getMaxAccelerationX() * getMoveDirection());
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
}

int Enemy::GetSpawnPointX()
{
	return spawn_point_x_;
}

int Enemy::GetSpawnPointY()
{
	return spawn_point_y_;
}

int Enemy::GetLineOfSight()
{
	return line_of_sight_;
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

void Enemy::SetSpawnPointX(int value)
{
	spawn_point_x_ = value;
}

void Enemy::SetSpawnPointY(int value)
{
	spawn_point_y_ = value;
}

void Enemy::SetLineOfSight(int value)
{
	line_of_sight_ = value;
}

void Enemy::SetPatrolRadius(int value)
{
	patrol_radius_ = value;
}
