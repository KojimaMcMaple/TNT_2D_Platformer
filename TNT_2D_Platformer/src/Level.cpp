#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::draw()
{
}

void Level::update()
{
}

void Level::clean()
{
}

int Level::GetLevelWidth()
{
	return width;
}

int Level::GetLevelHeight()
{
	return height;
}

int Level::GetTileWidth()
{
	return tile_width;
}

int Level::GetTileHeight()
{
	return tile_height;
}

int Level::GetCamPosX()
{
	return cam_pos_x;
}

int Level::GetCamPosY()
{
	return cam_pos_y;
}

int Level::GetVisibleTilesX()
{
	return TheGame::Instance()->GetWindowWidth() / tile_width;
}

int Level::GetVisibleTilesY()
{
	return TheGame::Instance()->GetWindowHeight() / tile_height;
}

int Level::GetLevelOffsetX()
{
	return cam_pos_x + GetVisibleTilesX() / 2;
}

int Level::GetLevelOffsetY()
{
	return cam_pos_y + GetVisibleTilesY() / 2;;
}

void Level::SetLevelWidth(int width)
{
	this->width = width;
}

void Level::SetLevelHeight(int height)
{
	this->height = height;
}

void Level::SetTileWidth(int width)
{
	tile_width = width;
}

void Level::SetTileHeight(int height)
{
	tile_height = height;
}

void Level::SetCamPosX(int x_coord)
{
	cam_pos_x = x_coord;
}

void Level::SetCamPosY(int y_coord)
{
	cam_pos_y = y_coord;
}
