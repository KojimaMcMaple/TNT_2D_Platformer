#include "Level.h"

Level::~Level()
{
}

Level::Level()
{
	setType(GameObjectType::LEVEL);
	SetTileWidth(64);
	SetTileHeight(64);
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
			visible_tile_dst_list_[index].x = x * GetTileWidth() - GetTileOffsetX();
			visible_tile_dst_list_[index].y = y * GetTileHeight() - GetTileOffsetY();
			tile_char = GetTileChar(x + GetTileIndexFromPosX(GetCamPosX()), y + GetTileIndexFromPosY(GetCamPosY()));
			switch (tile_char)
			{
			case 'G':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_01]->getTextureId(), tile_ptr_[CHURCH_GROUND_01]->getSrc(), &visible_tile_dst_list_[index], 0.0, 0, SDL_FLIP_NONE);
				break;
			case '#':
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_GROUND_02]->getTextureId(), tile_ptr_[CHURCH_GROUND_02]->getSrc(), &visible_tile_dst_list_[index], 0.0, 0, SDL_FLIP_NONE);
				break;
			default:
				TheTextureManager::Instance()->draw(renderer, tile_ptr_[CHURCH_BKG_01]->getTextureId(), tile_ptr_[CHURCH_BKG_01]->getSrc(), &visible_tile_dst_list_[index], 0.0, 0, SDL_FLIP_NONE);
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

void Level::LoadLevel(SDL_Renderer* renderer, std::string level_id)
{
	std::string level_raw_str = "";
	if (!visible_tile_dst_list_.empty()) {
		visible_tile_dst_list_.clear();
	}

	if (level_id == "church") {
		level_raw_str += "..G.............................................................";
		level_raw_str += "..G.............................................................";
		level_raw_str += ".......ooooo....................................................";
		level_raw_str += "........ooo.....................................................";
		level_raw_str += ".......................########.................................";
		level_raw_str += ".....BB?BBBB?BB.......###..............#.#......................";
		level_raw_str += "....................###................#.#......................";
		level_raw_str += ".................X.####.........................................";
		level_raw_str += "G.G.G.GGGGGGGGGGGGGGGGGGGGGGGGGGGGGG.#############......########";
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
	for (int i = -1; i < GetNumVisibleTilesX() + 1; i++) {
		for (int j = -1; j < GetNumVisibleTilesY() + 1; j++) {
			visible_tile_dst_list_.push_back(temp_rect);
		}
	}

	// Tileset uses src, tiles use dst
	tileset_ptr_[CHURCH_TILESET_01] = new Tile();
	tileset_ptr_[CHURCH_TILESET_01]->setTextureId("church_tileset_01");
	TheTextureManager::Instance()->load("../Assets/textures/church_tileset_01.png", tileset_ptr_[CHURCH_TILESET_01]->getTextureId(), renderer);
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

int Level::IsTileCharCollidable(char tile_char) {
	//0=solid block, 1=air/background, 2=consummables
	if (tile_char == '.') {
		return 1;
	}
	else {
		return 0;
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
	return Globals::sWindowWidth / GetTileWidth();
}

int Level::GetNumVisibleTilesY()
{
	return Globals::sWindowHeight / GetTileHeight();
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