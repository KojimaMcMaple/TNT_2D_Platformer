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
#include "LevelId.h"
#include "Tile.h"
#include "UI.h"

enum TileSetId {
	CHURCH_TILESET_01,
	CASTLE_TILESET_01,
	NUM_OF_TILESET_ID
};

enum TileId {
	CHURCH_BKG_00,
	CHURCH_BKG_01,
	CHURCH_CEILING_00,
	CHURCH_GROUND_00,
	CHURCH_GROUND_01,
	CHURCH_GROUND_02,
	CHURCH_BLOCK_00,
	CHURCH_BLOCK_01,
	CHURCH_BLOCK_02,
	NUM_OF_TILE_ID
};

class Level : public GameObject {
private:
	Uint8 bkg_r_value_;
	Uint8 bkg_g_value_;
	Uint8 bkg_b_value_;
	Uint8 bkg_a_value_;
	std::string level_raw_str_;
	int level_num_of_columns_;
	int level_num_of_rows_;
	Tile* tileset_texture_list_[NUM_OF_TILESET_ID];
	Tile* tile_texture_list_[NUM_OF_TILE_ID];
	std::vector<std::vector<Tile*>> level_world_tile_list_;
	std::vector<std::vector<Tile*>> visible_tile_list_; //only used for display
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

	int CheckWorldBounds(GameObject* obj_ptr);
	int CheckLevelCollision(GameObject* obj_ptr);
	void MapAllTileNeighbors();
	void BuildTileTextureDatabase();
	void MapAllTileTextureIdAndCollision();
	void LoadLevel(LevelId level_id);
	int GetLevelNumOfColumns();
	int GetLevelNumOfRows();
	int GetLevelTileWidth();
	int GetLevelTileHeight();
	int GetLevelMaxPosX();
	int GetLevelMaxPosY();
	int GetTileIndexFromPosX(int coord);
	int GetTileIndexFromPosY(int coord);
	int GetVisibleTilesNumOfColumns();
	int GetVisibleTilesNumOfRows();
	int GetCamPosX();
	int GetCamPosY();
	int GetCamCenterX();
	int GetCamCenterY();

	void SetBkgColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetLevelRawStr(std::string raw_str);
	void SetLevelNumOfColumns(int total_columns);
	void SetLevelNumOfRows(int total_rows);
	void SetLevelTileWidth(int width);
	void SetLevelTileHeight(int height);
	void SetCamPosX(int x_coord);
	void SetCamPosY(int y_coord);

	friend class Camera;
};

#endif