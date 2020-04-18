#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EnemyType.h"
#include "StatusBar.h"

class Enemy : public GameObject {
private:
	EnemyType enemy_type_;
	int spawn_point_x_;
	int spawn_point_y_;
	int patrol_radius_ = 50;
	int target_x_;
	int target_y_;
	StatusBar* m_statusBar;

	void InitSkeletonSword(int world_x = 0, int world_y = 0);
	void RenderSkeletonSword();
public:
	Enemy();
	Enemy(EnemyType type, int world_x, int world_y);
	~Enemy();

	void update() override;
	void draw() override;
	void clean() override;

	void MoveX();
	void StopX();
	void UpdatePosition();

	int GetSpawnPointX();
	int GetSpawnPointY();
	int GetPatrolRadius();
	int GetPatrolMinX();
	int GetPatrolMaxX();
	int GetTargetX();
	int GetTargetY();

	void SetSpawnPointX(int value);
	void SetSpawnPointY(int value);
	void SetPatrolRadius(int value);
	void SetTarget(int x, int y);

	StatusBar* getStatusBar();

	friend class Camera;
};


#endif /* defined (__Player__) */