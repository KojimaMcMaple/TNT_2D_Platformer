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
	int level_width_;
	int level_height_;
	Tile* tileset_ptr_[NUM_OF_TILESET_ID];
	Tile* tile_ptr_[NUM_OF_TILE_ID];
	std::vector<std::vector<SDL_Rect>> visible_tile_dst_list_;
	int tile_width_;
	int tile_height_;
	int cam_pos_x_;
	int cam_pos_y_;
public:
	Level();
	~Level();

	void update() override;
	void draw() override;
	void draw(SDL_Renderer* renderer);
	void clean() override;

	void LoadLevel(SDL_Renderer* renderer, std::string level_id);
	char GetTileChar(int x_index, int y_index);
	SDL_Rect* GetVisibleTileObj(int x_index, int y_index);
	int IsTileCharCollidable(char tile_char); //0=solid block, 1=air/background, 2=consummables
	bool WillCollideAABB(SDL_Rect* game_obj, int velocity);
	bool WillCollideRight(SDL_Rect* game_obj, int velocity);
	bool WillCollideLeft(SDL_Rect* game_obj, int velocity);
	bool WillCollideTop(SDL_Rect* game_obj, int velocity);
	bool WillCollideDown(SDL_Rect* game_obj, int velocity);
	void CollisionDebug(SDL_Rect* game_obj);
	int GetLevelWidth();
	int GetLevelHeight();
	int GetLevelMaxPosX();
	int GetLevelMaxPosY();
	int GetTileWidth();
	int GetTileHeight();
	int GetCamPosX();
	int GetCamPosY();
	int GetCamCenterX();
	int GetCamCenterY();
	int GetNumVisibleTilesX();
	int GetNumVisibleTilesY();
	int GetTileOffsetX();
	int GetTileOffsetY();
	int GetTileIndexFromPosX(int coord);
	int GetTileIndexFromPosY(int coord);

	void SetLevelRawStr(std::string raw_str);
	void SetTileChar(int x, int y, char in_char);
	void SetLevelWidth(int width);
	void SetLevelHeight(int height);
	void SetTileWidth(int width);
	void SetTileHeight(int height);
	void SetCamPosX(int x_coord);
	void SetCamPosY(int y_coord);
};

#endif