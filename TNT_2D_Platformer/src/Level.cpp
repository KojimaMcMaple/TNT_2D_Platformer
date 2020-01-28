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
	for (int i = -1; i < GetNumVisibleTilesX()+1; i++) {
		for (int j = -1; j < GetNumVisibleTilesY()+1; j++) {
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
	int index = -1;
	char tile_char = ' ';
	for (int x = -1; x < GetNumVisibleTilesX()+1; x++) {
		for (int y = -1; y < GetNumVisibleTilesY()+1; y++) {
			index = (y+1) * GetNumVisibleTilesX() + (x+1);
			visible_tile_dst_list_[index].x = x * GetTileWidth();
			visible_tile_dst_list_[index].y = y * GetTileHeight();
			tile_char = GetTileChar((int)(x + GetCamPosX() / GetTileWidth()), (int)(y + GetCamPosY() / GetTileHeight()));
			switch (tile_char)
			{
			case 'G':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_01]->getTextureId(), tile_ptr_[CHURCH_GROUND_01]->getSrc(), &visible_tile_dst_list_[index], 0.0, 0, SDL_FLIP_NONE);
				break;
			case '#':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_02]->getTextureId(), tile_ptr_[CHURCH_GROUND_02]->getSrc(), &visible_tile_dst_list_[index], 0.0, 0, SDL_FLIP_NONE);
				break;
			default:
				
				break;
			}
		}
	}
	/*char tile_char = ' ';
	for (int i = 0; i < GetLevelWidth(); i++) {
		for (int j = 0; j < GetLevelWidth(); j++) {
			SDL_Rect temp_rect = { -GetTileWidth(), -GetTileHeight(), GetTileWidth(), GetTileHeight() };
			temp_rect.x = i * GetTileWidth();
			temp_rect.y = j * GetTileHeight();
			tile_char = GetTileChar(i, j);
			switch (tile_char)
			{
			case 'G':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_02]->getTextureId(), tile_ptr_[CHURCH_GROUND_01]->getSrc(), &temp_rect, 0.0, 0, SDL_FLIP_NONE);
				break;
			default:
				break;
			}
		}
	}*/

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
	
	if (x > -1 && x < GetLevelWidth() && y > -1 && y < GetLevelHeight()) { // check bounds just in case
		return level_raw_str_[y * GetLevelWidth() + x]; //magic algorithm
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

int Level::GetLevelMaxPosX()
{
	return GetLevelWidth() * GetTileWidth();
}

int Level::GetLevelMaxPosY()
{
	return GetLevelHeight() * GetTileHeight();
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
	return Globals::sWindowWidth / GetTileWidth();
}

int Level::GetNumVisibleTilesY()
{
	return Globals::sWindowHeight / GetTileHeight();
}

int Level::GetTileOffsetX()
{
	return GetCamPosX() * GetTileWidth();
}

int Level::GetTileOffsetY()
{
	return GetCamPosY() * GetTileHeight();
}

void Level::SetTileChar(int x, int y, char in_char)
{
	if (x > -1 && x < GetLevelWidth() && y > -1 && y < GetLevelHeight()) {
		level_raw_str_[y * GetLevelWidth() + x] = in_char;
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
	if (x_coord < 0) {
		cam_pos_x_ = 0;
	}
	else if (x_coord + Globals::sWindowWidth > GetLevelWidth() * GetTileWidth()) {
		cam_pos_x_ = GetLevelWidth() * GetTileWidth() - Globals::sWindowWidth;
	}
	else {
		cam_pos_x_ = x_coord;
	}
}

void Level::SetCamPosY(int y_coord)
{
	if (y_coord < 0) {
		cam_pos_y_ = 0;
	}
	else if (y_coord + Globals::sWindowHeight > GetLevelHeight() * GetTileHeight()) {
		cam_pos_y_ = GetLevelHeight() * GetTileHeight() - Globals::sWindowHeight;
	}
	else {
		cam_pos_y_ = y_coord;
	}
}