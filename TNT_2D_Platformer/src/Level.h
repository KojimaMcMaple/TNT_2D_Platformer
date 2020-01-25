#pragma once
#ifndef __Level__
#define __Level__

#include <string>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Game.h"

class Level : public GameObject {
private:
	std::string level_source;
	int width;
	int height;
	int tile_width;
	int tile_height;
	int cam_pos_x;
	int cam_pos_y;
public:
	Level();
	~Level();

	void draw() override;
	void update() override;
	void clean() override;

	int GetLevelWidth();
	int GetLevelHeight();
	int GetTileWidth();
	int GetTileHeight();
	int GetCamPosX();
	int GetCamPosY();
	int GetVisibleTilesX();
	int GetVisibleTilesY();
	int GetLevelOffsetX();
	int GetLevelOffsetY();
	void SetLevelWidth(int width);
	void SetLevelHeight(int height);
	void SetTileWidth(int width);
	void SetTileHeight(int height);
	void SetCamPosX(int x_coord);
	void SetCamPosY(int y_coord);
};

#endif