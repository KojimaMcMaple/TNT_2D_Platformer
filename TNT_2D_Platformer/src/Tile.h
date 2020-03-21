#pragma once
#ifndef __Tile__
#define __Tile__

#include "GameObject.h"
#include "TextureManager.h"
#include "TileNeighbour.h"

class Tile : public GameObject {
private:
	char tile_char_;
	int texture_id_;
	
	std::vector<Tile*> m_pNeighbours;
public:
	Tile();
	~Tile();

	void update() override;
	void draw() override;
	void clean() override;

	// get neighbours
	Tile* getUp();
	Tile* getDown();
	Tile* getRight();
	Tile* getLeft();

	// set neighbours
	void setUp(Tile* tile);
	void setDown(Tile* tile);
	void setRight(Tile* tile);
	void setLeft(Tile* tile);
};

#endif