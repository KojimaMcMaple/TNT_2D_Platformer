#pragma once
#ifndef __Level__
#define __Level__

#include <string>
#include <vector>
#include "Globals.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"

enum TileSetId {
	CHURCH_TILESET_01,
	NUM_OF_TILESET_ID
};

enum TileId {
	CHURCH_GROUND_01,
	CHURCH_GROUND_02,
	NUM_OF_TILE_ID
};

class Level : public GameObject {
private:
	std::string level_raw_str_;
	int level_width_;
	int level_height_;
	int in_level_offset_x_;
	int in_level_offset_y_;
	Tile* tileset_ptr_[NUM_OF_TILESET_ID];
	Tile* tile_ptr_[NUM_OF_TILE_ID];
	std::vector<SDL_Rect> visible_tile_dst_list_;
	int tile_width_;
	int tile_height_;
	int cam_pos_x_;
	int cam_pos_y_;
public:
	Level();
	~Level();
	Level(SDL_Renderer* renderer);

	void update() override;
	void draw() override;
	void draw(SDL_Renderer* renderer);
	void clean() override;

	void LoadLevel(std::string in_str);
	char GetTileChar(int x, int y);
	int GetLevelWidth();
	int GetLevelHeight();
	int GetLevelMaxPosX();
	int GetLevelMaxPosY();
	int GetTileWidth();
	int GetTileHeight();
	int GetCamPosX();
	int GetCamPosY();
	int GetNumVisibleTilesX();
	int GetNumVisibleTilesY();
	int GetLevelOffsetX();
	int GetLevelOffsetY();
	int GetInLevelOffsetX();
	int GetInLevelOffsetY();
	int GetTileOffsetX();
	int GetTileOffsetY();

	void SetTileChar(int x, int y, char in_char);
	void SetLevelWidth(int width);
	void SetLevelHeight(int height);
	void SetTileWidth(int width);
	void SetTileHeight(int height);
	void SetCamPosX(int x_coord);
	void SetCamPosY(int y_coord);
	void SetInLevelOffsetX(int x_distance);
	void SetInLevelOffsetY(int y_distance);
};

#endif