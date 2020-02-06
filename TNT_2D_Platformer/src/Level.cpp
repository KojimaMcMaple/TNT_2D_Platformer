#include "Level.h"
#include "Game.h"

Level::Level()
{
	setType(GameObjectType::LEVEL);
	SetTileWidth(64);
	SetTileHeight(64);
}

Level::~Level()
{
}

void Level::update()
{
	for (int x = 0; x < GetNumVisibleTilesX(); x++) {
		for (int y = 0; y < GetNumVisibleTilesY(); y++) {
			visible_tile_dst_list_[x][y].x = x * GetTileWidth() - GetTileOffsetX();
			visible_tile_dst_list_[x][y].y = y * GetTileHeight() - GetTileOffsetY();
		}
	}
}

void Level::draw()
{
	char tile_char = ' ';
	for (int x = 0; x < GetNumVisibleTilesX(); x++) {
		for (int y = 0; y < GetNumVisibleTilesY(); y++) {
			tile_char = GetTileChar(x + GetTileIndexFromPosX(GetCamPosX()), y + GetTileIndexFromPosY(GetCamPosY()));
			//if (x == -1 && y == -1) {
			//	std::cout << "tile_char =" << tile_char << std::endl;
			//}
			switch (tile_char)
			{
			case 'G':
				TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), tile_ptr_[CHURCH_GROUND_01]->getTextureId(), tile_ptr_[CHURCH_GROUND_01]->getSrc(), &visible_tile_dst_list_[x][y], 0.0, 0, SDL_FLIP_NONE);
				break;
			case '#':
				TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), tile_ptr_[CHURCH_GROUND_02]->getTextureId(), tile_ptr_[CHURCH_GROUND_02]->getSrc(), &visible_tile_dst_list_[x][y], 0.0, 0, SDL_FLIP_NONE);
				break;
			case '@':
				TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), tile_ptr_[CHURCH_BLOCK_01]->getTextureId(), tile_ptr_[CHURCH_BLOCK_01]->getSrc(), &visible_tile_dst_list_[x][y], 0.0, 0, SDL_FLIP_NONE);
				break;
			default:
				TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), tile_ptr_[CHURCH_BKG_01]->getTextureId(), tile_ptr_[CHURCH_BKG_01]->getSrc(), &visible_tile_dst_list_[x][y], 0.0, 0, SDL_FLIP_NONE);
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

void Level::LoadLevel(std::string level_id)
{
	std::string level_raw_str = "";
	if (!visible_tile_dst_list_.empty()) {
		visible_tile_dst_list_.clear();
	}

	if (level_id == "church") {
		level_raw_str += "G.G.............................................................";
		level_raw_str += "................................................................";
		level_raw_str += "G.G.............................................................";
		level_raw_str += "................................................................";
		level_raw_str += "G......................########.................................";
		level_raw_str += "......................###..............#.#......................";
		level_raw_str += "G...................###................#.#......................";
		level_raw_str += "...................####.........................................";
		level_raw_str += "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG.##########.........########";
		level_raw_str += "........................############.#...............###........";
		level_raw_str += "........................#............#............###...........";
		level_raw_str += "........................#............#.........###..............";
		level_raw_str += "........................#.############......###.................";
		level_raw_str += "........................#................###....................";
		level_raw_str += "........................#..............##.......................";
		level_raw_str += "........................################........................";

		SetLevelRawStr(level_raw_str);
		SetLevelWidth(64);
		SetLevelHeight(16);
	}

	SDL_Rect temp_rect = { -GetTileWidth(), -GetTileHeight(), GetTileWidth(), GetTileHeight() };
	for (int i = 0; i < GetNumVisibleTilesX(); i++) {
		std::vector<SDL_Rect> temp;
		temp.clear();
		for (int j = 0; j < GetNumVisibleTilesY(); j++) {
			temp.push_back(temp_rect);
		}
		visible_tile_dst_list_.push_back(temp);
	}

	// Tileset uses src, tiles use dst
	tileset_ptr_[CHURCH_TILESET_01] = new Tile();
	tileset_ptr_[CHURCH_TILESET_01]->setTextureId("church_tileset_01");
	TheTextureManager::Instance()->load("../Assets/textures/church_tileset_01.png", tileset_ptr_[CHURCH_TILESET_01]->getTextureId(), TheGame::Instance()->getRenderer());
	//tileset_ptr_[CHURCH_TILESET_01]->setSrc(0, 0, 336, 224);
	//tileset_ptr_[CHURCH_TILESET_01]->setIsColliding(false);

	tile_ptr_[CHURCH_BKG_01] = new Tile();
	tile_ptr_[CHURCH_BKG_01]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_BKG_01]->setSrc(128, 16, 15, 15);
	tile_ptr_[CHURCH_BKG_01]->setIsColliding(false);

	tile_ptr_[CHURCH_GROUND_01] = new Tile();
	tile_ptr_[CHURCH_GROUND_01]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_GROUND_01]->setSrc(64, 168, 47, 39);
	tile_ptr_[CHURCH_GROUND_01]->setIsColliding(true);

	tile_ptr_[CHURCH_GROUND_02] = new Tile();
	tile_ptr_[CHURCH_GROUND_02]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_GROUND_02]->setSrc(128, 168, 47, 39);
	tile_ptr_[CHURCH_GROUND_02]->setIsColliding(true);

	tile_ptr_[CHURCH_BLOCK_01] = new Tile();
	tile_ptr_[CHURCH_BLOCK_01]->setTextureId(tileset_ptr_[CHURCH_TILESET_01]->getTextureId());
	tile_ptr_[CHURCH_BLOCK_01]->setSrc(16, 112, 31, 31);
	tile_ptr_[CHURCH_BLOCK_01]->setIsColliding(true);
}

char Level::GetTileChar(int x_index, int y_index)
{
	if (x_index > -1 && x_index < GetLevelWidth() && y_index > -1 && y_index < GetLevelHeight()) { // check bounds just in case
		return level_raw_str_[y_index * GetLevelWidth() + x_index]; //magic algorithm
	}
	else {
		return ' ';
	}
}

SDL_Rect* Level::GetVisibleTileObj(int x_index, int y_index)
{
	if (x_index > -1 && x_index < GetNumVisibleTilesX() && y_index > -1 && y_index < GetNumVisibleTilesY()) { // check bounds just in case
		return &visible_tile_dst_list_[x_index][y_index];
	}
	else {
		SDL_Rect temp = { 0,0,0,0 };
		return &temp;
	}
}

int Level::IsTileCharCollidable(char tile_char) {
	//0=solid block, 1=air/background, 2=consummables
	if (tile_char == 'G' || tile_char == '#' || tile_char == '@') {
		return 0;
	}
	else {
		return 1;
	}
}

void Level::CollisionDebug(SDL_Rect* game_obj)
{
	std::vector<int> result;
	for (int x = 0; x < GetNumVisibleTilesX(); x++) {
		for (int y = 0; y < GetNumVisibleTilesY(); y++) {
			//std::cout << "x = " << x << std::endl;
			//std::cout << "y = " << y << std::endl;
			//std::cout << "index = " << index << std::endl;
			//std::cout << "X = " << visible_tile_dst_list_[index].x << std::endl;
			//std::cout << "Y = " << visible_tile_dst_list_[index].y << std::endl;
			if (CollisionManager::HaveCollidedAABB(game_obj, &(visible_tile_dst_list_[x][y]))) {
				SetTileChar(x + GetTileIndexFromPosX(GetCamPosX()), y + GetTileIndexFromPosY(GetCamPosY()), '@');
				result.push_back(x);
			}
			//else {
			//	std::cout << "X1 = " << game_obj->x << std::endl;
			//	std::cout << "X2 = " << temp_ptr->x << std::endl;
			//}
			//if (x == -1 && y == -1) {
			//	std::cout << "x = " << x << std::endl;
			//	std::cout << "y = " << y << std::endl;
			//	std::cout << "index = " << index << std::endl;
			//	std::cout << "X1 = " << game_obj->x << std::endl;
			//	std::cout << "X2 = " << temp_ptr->x << std::endl;
			//}
		}
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

int Level::GetCamCenterX()
{
	return cam_pos_x_ + Globals::sWindowWidth / 2;
}

int Level::GetCamCenterY()
{
	return cam_pos_y_ + Globals::sWindowHeight / 2;
}

int Level::GetNumVisibleTilesX()
{
	return Globals::sWindowWidth / GetTileWidth() + 1;
}

int Level::GetNumVisibleTilesY()
{
	return Globals::sWindowHeight / GetTileHeight() + 1;
}

int Level::GetTileOffsetX()
{
	// FIND STARTING COORD OF NEAREST TILE
	int nearest_tile_starting_coord = GetTileIndexFromPosX(GetCamPosX()) * GetTileWidth();

	// RETURN OFFSET
	return (GetCamPosX() - nearest_tile_starting_coord);
}

int Level::GetTileOffsetY()
{
	// FIND STARTING COORD OF NEAREST TILE
	int nearest_tile_starting_coord = GetTileIndexFromPosY(GetCamPosY()) * GetTileHeight();

	// RETURN OFFSET
	return (GetCamPosY() - nearest_tile_starting_coord);
}

int Level::GetTileIndexFromPosX(int coord) {
	return int(coord / GetTileWidth());
}

int Level::GetTileIndexFromPosY(int coord) {
	return int(coord / GetTileHeight());
}

void Level::SetLevelRawStr(std::string raw_str)
{
	level_raw_str_ = raw_str;
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