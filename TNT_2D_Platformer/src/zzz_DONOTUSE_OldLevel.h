#pragma once
#ifndef __Level__
#define __Level__

#include <string>
#include <vector>
#include "Globals.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "UI.h"

enum TileSetId {
	CHURCH_TILESET_01,
	NUM_OF_TILESET_ID
};

enum TileId {
	CHURCH_BKG_01,
	CHURCH_GROUND_01,
	CHURCH_GROUND_02,
	CHURCH_BLOCK_01,
	NUM_OF_TILE_ID
};

class Level : public GameObject {
private:
	std::string level_raw_str_;
	int level_num_of_columns_;
	int level_num_of_rows_;
	Tile* tileset_texture_list_[NUM_OF_TILESET_ID];
	Tile* tile_texture_list_[NUM_OF_TILE_ID];
	std::vector<std::vector<SDL_Rect>> visible_tile_list_;
	int level_tile_width_;
	int level_tile_height_;
	int cam_pos_x_;
	int cam_pos_y_;
	UI* ui_pause_ptr_;
	UI* ui_quit_ptr_;

public:
	Level();
	~Level();

	void update() override;
	void draw() override;
	void clean() override;

	void LoadLevel(std::string level_id);
	char GetTileChar(int x_index, int y_index);
	SDL_Rect* GetVisibleTileObj(int x_index, int y_index);
	int IsTileCharCollidable(char tile_char); //0=solid block, 1=air/background, 2=consummables
	void CollisionDebug(SDL_Rect* game_obj);
	int GetLevelNumOfColumns();
	int GetLevelNumOfRows();
	int GetLevelMaxPosX();
	int GetLevelMaxPosY();
	int GetLevelTileWidth();
	int GetLevelTileHeight();
	int GetCamPosX();
	int GetCamPosY();
	int GetCamCenterX();
	int GetCamCenterY();
	int GetVisibleTilesNumOfColumns();
	int GetVisibleTilesNumOfRows();
	int GetTileOffsetX();
	int GetTileOffsetY();
	int GetTileIndexFromPosX(int coord);
	int GetTileIndexFromPosY(int coord);

	void SetLevelRawStr(std::string raw_str);
	void SetTileChar(int x, int y, char in_char);
	void SetLevelNumOfColumns(int width);
	void SetLevelNumOfRows(int height);
	void SetLevelTileWidth(int width);
	void SetLevelTileHeight(int height);
	void SetCamPosX(int x_coord);
	void SetCamPosY(int y_coord);
};

#endif