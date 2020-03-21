#include "Level.h"
#include "Game.h"

Level::Level()
{
	setType(GameObjectType::LEVEL);
	SetTileWidth(64);
	SetTileHeight(64);
	ui_pause_ptr_ = new UI("pause_text", "../Assets/textures/press P to pause.png", 0, 0, 321, 44, 800, 10, 321 / 2, 44 / 2);
	ui_quit_ptr_ = new UI("quit_text", "../Assets/textures/press X to quit.png", 0, 0, 296, 46, 800, 50, 296 / 2, 46 / 2);
}

Level::~Level()
{
}

void Level::update()
{
	
}

void Level::draw()
{
	

	ui_pause_ptr_->draw();
	ui_quit_ptr_->draw();
}

void Level::clean()
{
}

void Level::LoadLevel(std::string level_id)
{
	// NUKE PREVIOUS LEVEL (IF ANY)
	std::string level_raw_str = "";
	if (!level_tile_list_.empty()) {
		level_tile_list_.clear();
	}

	// BUILD LEVEL
	if (level_id == "church") {
		level_raw_str += ".......................................................................................";
		level_raw_str += ".......................................................................................";
		level_raw_str += ".......................................................................................";
		level_raw_str += ".......................................................................................";
		level_raw_str += "......................#########........................................................";
		level_raw_str += ".....................####..............................................................";
		level_raw_str += "....................###.........................................#......................";
		level_raw_str += "...................###.........................................###.....................";
		level_raw_str += "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG.##########.####....###############################";
		level_raw_str += "........................############.#...............###...............................";
		level_raw_str += "........................#............#............###..................................";
		level_raw_str += "........................#............#.........###.....................................";
		level_raw_str += "........................#.############......###........................................";
		level_raw_str += "........................#................###...........................................";
		level_raw_str += "........................#..............##..............................................";
		level_raw_str += "........................################...............................................";

		SetLevelRawStr(level_raw_str);
		SetLevelNumOfRows(16);
		SetLevelNumOfColumns(level_raw_str.size()/GetLevelNumOfRows());
	}

	std::vector<std::vector<char>> level_raw_str_list;
	level_raw_str_list.resize(GetLevelNumOfRows(), std::vector<char>(GetLevelNumOfColumns(), '.'));
	for (int row = 0; row < GetLevelNumOfRows(); row++) {
		for (int col = 0; col < GetLevelNumOfColumns(); col++) {
			//1D to 2D arr fomula: array2d[row][col] = array1d[(row * no_of_col) + col]; 
			level_raw_str_list[row][col] = level_raw_str[row * GetLevelNumOfColumns() + col];
		}
	}

	level_tile_list_.resize(GetLevelNumOfRows(), std::vector<SDL_Rect*>(GetLevelNumOfColumns(), nullptr));
	for (int row = 0; row < GetLevelNumOfRows(); row++) {
		for (int col = 0; col < GetLevelNumOfColumns(); col++) {
			SDL_Rect temp_rect = { col * GetTileWidth(), row * GetTileHeight(), GetTileWidth(), GetTileHeight() };
			level_tile_list_[row][col] = 
		}
	}

	// Tileset uses src, tiles use dst
	tileset_texture_list_[CHURCH_TILESET_01] = new Tile();
	tileset_texture_list_[CHURCH_TILESET_01]->setTextureId("church_tileset_01");
	TheTextureManager::Instance()->load("../Assets/textures/church_tileset_01.png", tileset_texture_list_[CHURCH_TILESET_01]->getTextureId(), TheGame::Instance()->getRenderer());
	//tileset_texture_list_[CHURCH_TILESET_01]->setSrc(0, 0, 336, 224);
	//tileset_texture_list_[CHURCH_TILESET_01]->setIsColliding(false);

	tile_texture_list_[CHURCH_BKG_01] = new Tile();
	tile_texture_list_[CHURCH_BKG_01]->setTextureId(tileset_texture_list_[CHURCH_TILESET_01]->getTextureId());
	tile_texture_list_[CHURCH_BKG_01]->setSrc(128, 16, 15, 15);
	tile_texture_list_[CHURCH_BKG_01]->setIsColliding(false);

	tile_texture_list_[CHURCH_GROUND_01] = new Tile();
	tile_texture_list_[CHURCH_GROUND_01]->setTextureId(tileset_texture_list_[CHURCH_TILESET_01]->getTextureId());
	tile_texture_list_[CHURCH_GROUND_01]->setSrc(64, 168, 47, 39);
	tile_texture_list_[CHURCH_GROUND_01]->setIsColliding(true);

	tile_texture_list_[CHURCH_GROUND_02] = new Tile();
	tile_texture_list_[CHURCH_GROUND_02]->setTextureId(tileset_texture_list_[CHURCH_TILESET_01]->getTextureId());
	tile_texture_list_[CHURCH_GROUND_02]->setSrc(128, 168, 47, 39);
	tile_texture_list_[CHURCH_GROUND_02]->setIsColliding(true);

	tile_texture_list_[CHURCH_BLOCK_01] = new Tile();
	tile_texture_list_[CHURCH_BLOCK_01]->setTextureId(tileset_texture_list_[CHURCH_TILESET_01]->getTextureId());
	tile_texture_list_[CHURCH_BLOCK_01]->setSrc(16, 112, 31, 31);
	tile_texture_list_[CHURCH_BLOCK_01]->setIsColliding(true);
}

char Level::GetTileChar(int x_index, int y_index)
{
	if (x_index > -1 && x_index < GetLevelNumOfColumns() && y_index > -1 && y_index < GetLevelNumOfRows()) { // check bounds just in case
		return level_raw_str_[y_index * GetLevelNumOfColumns() + x_index]; //magic algorithm
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
		/*SDL_Rect temp = { 0,0,0,0 };
		return &temp;*/
		return nullptr;
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

int Level::GetLevelNumOfColumns()
{
	return level_num_of_columns_;
}

int Level::GetLevelNumOfRows()
{
	return level_num_of_rows_;
}

int Level::GetLevelMaxPosX()
{
	return GetLevelNumOfColumns() * GetTileWidth();
}

int Level::GetLevelMaxPosY()
{
	return GetLevelNumOfRows() * GetTileHeight();
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
	if (x > -1 && x < GetLevelNumOfColumns() && y > -1 && y < GetLevelNumOfRows()) {
		level_raw_str_[y * GetLevelNumOfColumns() + x] = in_char;
	}
}

void Level::SetLevelNumOfColumns(int total_columns)
{
	this->level_num_of_columns_ = total_columns;
}

void Level::SetLevelNumOfRows(int total_rows)
{
	this->level_num_of_rows_ = total_rows;
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
	else if (x_coord + Globals::sWindowWidth > GetLevelNumOfColumns() * GetTileWidth()) {
		cam_pos_x_ = GetLevelNumOfColumns() * GetTileWidth() - Globals::sWindowWidth;
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
	else if (y_coord + Globals::sWindowHeight > GetLevelNumOfRows() * GetTileHeight()) {
		cam_pos_y_ = GetLevelNumOfRows() * GetTileHeight() - Globals::sWindowHeight;
	}
	else {
		cam_pos_y_ = y_coord;
	}
}