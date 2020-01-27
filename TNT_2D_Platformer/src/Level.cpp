#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

Level::Level(SDL_Renderer* renderer)
{
	setType(GameObjectType::LEVEL);
	SetTileWidth(64);
	SetTileHeight(64);
	SDL_Rect temp_rect = { -GetTileWidth(), -GetTileHeight(), GetTileWidth(), GetTileHeight() };
	for (int i = 0; i < GetNumVisibleTilesX(); i++) {
		for (int j = 0; j < GetNumVisibleTilesY(); j++) {
			visible_tile_dst_list_.push_back(temp_rect);
		}
	}

	// Tileset uses src, tiles use dst
	tileset_ptr_[CHURCH_TILESET_01] = new Tile();
	tileset_ptr_[CHURCH_TILESET_01]->setTextureId("church_tileset_01");
	TheTextureManager::Instance()->load("../Assets/textures/church_tileset_01.png", tileset_ptr_[CHURCH_TILESET_01]->getTextureId(), renderer);
	tileset_ptr_[CHURCH_TILESET_01]->setSrc(0, 0, 336, 224);
	tileset_ptr_[CHURCH_TILESET_01]->setIsColliding(false);

	tile_ptr_[CHURCH_GROUND_01] = new Tile();
	tile_ptr_[CHURCH_GROUND_01]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_GROUND_01]->setSrc(64, 167, 47, 40);
	tile_ptr_[CHURCH_GROUND_01]->setIsColliding(true);

	tile_ptr_[CHURCH_GROUND_02] = new Tile();
	tile_ptr_[CHURCH_GROUND_02]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_GROUND_02]->setSrc(128, 167, 47, 40);
	tile_ptr_[CHURCH_GROUND_02]->setIsColliding(true);
}

void Level::update()
{

}

void Level::draw()
{
}

void Level::draw(SDL_Renderer* renderer)
{
	for (int x = 0; x < GetNumVisibleTilesX(); x++) {
		for (int y = 0; y < GetNumVisibleTilesY(); y++) {
			visible_tile_dst_list_[y * GetNumVisibleTilesY() + x].x = x * GetTileWidth();
			visible_tile_dst_list_[y * GetNumVisibleTilesY() + x].y = y * GetTileHeight();
			char tile_char = GetTileChar(x + GetLevelOffsetX(), y + GetLevelOffsetY());
			switch (tile_char)
			{
			case 'G':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_01]->getTextureId(), tile_ptr_[CHURCH_GROUND_01]->getSrc(), &visible_tile_dst_list_[y * GetNumVisibleTilesY() + x], 0.0, 0, SDL_FLIP_NONE);
			case '#':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_02]->getTextureId(), tile_ptr_[CHURCH_GROUND_02]->getSrc(), &visible_tile_dst_list_[y * GetNumVisibleTilesY() + x], 0.0, 0, SDL_FLIP_NONE);
			default:
				
				//Fill(x * GetTileWidth(), y * GetTileHeight(), (x) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_BLACK);
				break;
			}
		}
	}
}

void Level::clean()
{
}

void Level::LoadLevel(std::string in_str)
{
	level_raw_str_ = in_str;

}

char Level::GetTileChar(int x, int y)
{
	if (x > -1 && x < level_width_ && y > -1 && y < level_height_) { // check bounds just in case
		return level_raw_str_[y * level_width_ + x]; //magic algorithm
	}
	else {
		return ' ';
	}
}

int Level::GetLevelWidth()
{
	return level_width_;
}

int Level::GetLevelHeight()
{
	return level_height_;
}

int Level::GetTileWidth()
{
	return tile_width_;
}

int Level::GetTileHeight()
{
	return tile_height_;
}

int Level::GetCamPosX()
{
	return cam_pos_x_;
}

int Level::GetCamPosY()
{
	return cam_pos_y_;
}

int Level::GetNumVisibleTilesX()
{
	return Globals::sWindowWidth / tile_width_;
}

int Level::GetNumVisibleTilesY()
{
	return Globals::sWindowHeight / tile_height_;
}

int Level::GetLevelOffsetX()
{
	int result = cam_pos_x_ + GetNumVisibleTilesX() / 2;
	if (result < 0) {
		result = 0;
	}
	if (result > GetLevelWidth() - GetNumVisibleTilesX()) {
		result = GetLevelWidth() - GetNumVisibleTilesX();
	}
	return result;
}

int Level::GetLevelOffsetY()
{
	int result = cam_pos_y_ + GetNumVisibleTilesY() / 2;
	if (result < 0) {
		result = 0;
	}
	if (result > GetLevelHeight() - GetNumVisibleTilesY()) {
		result = GetLevelHeight() - GetNumVisibleTilesY();
	}
	return result;
}

void Level::SetTileChar(int x, int y, char in_char)
{
	if (x > -1 && x < level_width_ && y > -1 && y < level_height_) {
		level_raw_str_[y * level_width_ + x] = in_char;
	}
}

void Level::SetLevelWidth(int width)
{
	this->level_width_ = width;
}

void Level::SetLevelHeight(int height)
{
	this->level_height_ = height;
}

void Level::SetTileWidth(int width)
{
	tile_width_ = width;
}

void Level::SetTileHeight(int height)
{
	tile_height_ = height;
}

void Level::SetCamPosX(int x_coord)
{
	cam_pos_x_ = x_coord;
}

void Level::SetCamPosY(int y_coord)
{
	cam_pos_y_ = y_coord;
}
