#pragma once
#ifndef __Tile__
#define __Tile__

#include "GameObject.h"
#include "TextureManager.h"

class Tile : public GameObject {
private:
public:
	Tile();
	~Tile();

	void update() override;
	void draw() override;
	void clean() override;
};

#endif