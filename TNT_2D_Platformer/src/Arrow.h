#pragma once
#include "GameObject.h"
#include <string>

class Arrow : public GameObject
{

public:
	Arrow(int x, int y, int direction);
	~Arrow();

	void update() override;
	void draw() override;
	void clean() override;

	friend class Camera;
};

