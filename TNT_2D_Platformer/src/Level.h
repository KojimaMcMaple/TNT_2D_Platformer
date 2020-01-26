#pragma once
#ifndef __Level__
#define __Level__

#include <string>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Globals.h"

class Level : public GameObject {
private:
	std::string level_raw_str_;
	int width_;
	int height_;
	int tile_width_;
	int tile_height_;
	int cam_pos_x_;
	int cam_pos_y_;
public:
	Level();
	~Level();

	void update() override;
	void draw() override;
	void clean() override;

	void LoadLevel(std::string in_str);
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