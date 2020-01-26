#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::update()
{

}

void Level::draw()
{
}

void Level::clean()
{
}

void Level::LoadLevel(std::string in_str)
{
	level_raw_str_ = in_str;

}

int Level::GetLevelWidth()
{
	return width_;
}

int Level::GetLevelHeight()
{
	return height_;
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

int Level::GetVisibleTilesX()
{
	return Globals::sWindowWidth / tile_width_;
}

int Level::GetVisibleTilesY()
{
	return Globals::sWindowHeight / tile_height_;
}

int Level::GetLevelOffsetX()
{
	return cam_pos_x_ + GetVisibleTilesX() / 2;
}

int Level::GetLevelOffsetY()
{
	return cam_pos_y_ + GetVisibleTilesY() / 2;;
}

void Level::SetLevelWidth(int width)
{
	this->width_ = width;
}

void Level::SetLevelHeight(int height)
{
	this->height_ = height;
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
