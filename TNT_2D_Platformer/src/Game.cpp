#include "Game.h"
#include "Util.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
}

Game::~Game()
{
}

glm::vec2 Game::getTargetPosition()
{
	return glm::vec2(0,0);
}

SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

int Game::GetOffsetPositionX()
{
	return offset_position_x_;
}

int Game::GetOffsetPositionY()
{
	return offset_position_y_;
}

void Game::SetOffsetPositionX(int x_distance)
{
	offset_position_x_ = x_distance;
}

void Game::SetOffsetPositionY(int y_distance)
{
	offset_position_y_ = y_distance;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

void Game::createGameObjects()
{
	std::cout << "MEOW" << std::endl;

	level_ptr_ = new Level();
	level_ptr_->LoadLevel(getRenderer(), "church");

	player_ptr_ = new Player(getRenderer());
	player_ptr_->setDstXAndHitBox(4 * level_ptr_->GetTileWidth() + level_ptr_->GetTileWidth() / 2 - player_ptr_->getDstW() / 2);
	player_ptr_->setDstYAndHitBox(4 * level_ptr_->GetTileHeight() + level_ptr_->GetTileHeight() / 2 - player_ptr_->getDstH() / 2);

	// CENTER CAM TO PLAYER
	level_ptr_->SetCamPosX(player_ptr_->getDstX() - Globals::sWindowWidth / 2 + player_ptr_->getDstW() / 2);
	level_ptr_->SetCamPosY(player_ptr_->getDstY() - Globals::sWindowHeight / 2 + player_ptr_->getDstH() / 2);
	//std::cout << TheTextureManager::Instance();
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

				// ENABLE ALPHA BLENDING
				SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}
	key_states_ = SDL_GetKeyboardState(nullptr);
	
	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

bool Game::isKeyDown(SDL_Scancode keyboard_code)
{
	if (key_states_ != nullptr) {
		if (key_states_[keyboard_code]) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				m_bRunning = false;
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	player_ptr_->setVelocityX(0);
	player_ptr_->setVelocityY(0);

	// PROCESSING, HAPPENS WHEN KEYS ARE HELD DOWN
	if (s_pInstance->isKeyDown(SDL_SCANCODE_W) || s_pInstance->isKeyDown(SDL_SCANCODE_UP)) {
		player_ptr_->setVelocityY(-6);
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_S) || s_pInstance->isKeyDown(SDL_SCANCODE_DOWN)) {
		player_ptr_->setVelocityY(6);
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_A) || s_pInstance->isKeyDown(SDL_SCANCODE_LEFT)) {
		player_ptr_->setVelocityX(-6);
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_D) || s_pInstance->isKeyDown(SDL_SCANCODE_RIGHT)) {
		player_ptr_->setVelocityX(6);
	}

	level_ptr_->update();
	// COLLISION
	//level_ptr_->CollisionProcessing(player_ptr_->getHitBox());
	//level_ptr_->CollisionDebug(player_ptr_->getHitBox());
	// MOVE RIGHT
	int index_left_x = level_ptr_->GetTileIndexFromPosX(player_ptr_->getHitBoxX() + level_ptr_->GetTileOffsetX()); //offset to handle screen-scrolling, fixed the issue of player not mapped correctly to an offseted tile
	int index_right_x = level_ptr_->GetTileIndexFromPosX(player_ptr_->getHitBoxRightmostX() + level_ptr_->GetTileOffsetX());
	int index_mid_x = (int)(index_left_x + index_right_x) / 2;
	int index_top_y = level_ptr_->GetTileIndexFromPosY(player_ptr_->getHitBoxY() + level_ptr_->GetTileOffsetY());
	int index_down_y = level_ptr_->GetTileIndexFromPosY(player_ptr_->getHitBoxLowermostY() + level_ptr_->GetTileOffsetY());
	int index_mid_y = (int)(index_top_y + index_down_y) / 2; //player may occupy 3 vertical tiles so this is needed, fixed the issue of the center of player going through tiles
	int next_index_left_x = index_left_x;
	int next_index_right_x = index_right_x;
	int next_index_top_y = index_top_y;
	int next_index_down_y = index_down_y;
	if (index_left_x > 0) {
		next_index_left_x = index_left_x - 1;
	}
	if (index_right_x < level_ptr_->GetNumVisibleTilesX()) {
		next_index_right_x = index_right_x + 1;
	}
	if (index_top_y > 0) {
		next_index_top_y = index_top_y - 1;
	}
	if (index_down_y < level_ptr_->GetNumVisibleTilesY()) {
		next_index_down_y = index_down_y + 1;
	}

	SDL_Rect* next_left_tile_top = level_ptr_->GetVisibleTileObj(next_index_left_x, index_top_y);
	SDL_Rect* next_left_tile_mid = level_ptr_->GetVisibleTileObj(next_index_left_x, index_mid_y);
	SDL_Rect* next_left_tile_down = level_ptr_->GetVisibleTileObj(next_index_left_x, index_down_y);
	SDL_Rect* next_right_tile_top = level_ptr_->GetVisibleTileObj(next_index_right_x, index_top_y);
	SDL_Rect* next_right_tile_mid = level_ptr_->GetVisibleTileObj(next_index_right_x, index_mid_y);
	SDL_Rect* next_right_tile_down = level_ptr_->GetVisibleTileObj(next_index_right_x, index_down_y);
	char next_left_tile_top_char = level_ptr_->GetTileChar(next_index_left_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_top_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_left_tile_mid_char = level_ptr_->GetTileChar(next_index_left_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_mid_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_left_tile_down_char = level_ptr_->GetTileChar(next_index_left_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_down_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_right_tile_top_char = level_ptr_->GetTileChar(next_index_right_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_top_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_right_tile_mid_char = level_ptr_->GetTileChar(next_index_right_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_mid_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_right_tile_down_char = level_ptr_->GetTileChar(next_index_right_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), index_down_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	
	SDL_Rect* next_top_tile_left = level_ptr_->GetVisibleTileObj(index_left_x, next_index_top_y);
	SDL_Rect* next_top_tile_mid = level_ptr_->GetVisibleTileObj(index_mid_x, next_index_top_y);
	SDL_Rect* next_top_tile_right = level_ptr_->GetVisibleTileObj(index_right_x, next_index_top_y);	
	SDL_Rect* next_down_tile_left = level_ptr_->GetVisibleTileObj(index_left_x, next_index_down_y);
	SDL_Rect* next_down_tile_mid = level_ptr_->GetVisibleTileObj(index_mid_x, next_index_down_y);
	SDL_Rect* next_down_tile_right = level_ptr_->GetVisibleTileObj(index_right_x, next_index_down_y);
	char next_top_tile_left_char = level_ptr_->GetTileChar(index_left_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_top_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_top_tile_mid_char = level_ptr_->GetTileChar(index_mid_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_top_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_top_tile_right_char = level_ptr_->GetTileChar(index_right_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_top_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_down_tile_left_char = level_ptr_->GetTileChar(index_left_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_down_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_down_tile_mid_char = level_ptr_->GetTileChar(index_mid_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_down_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));
	char next_down_tile_right_char = level_ptr_->GetTileChar(index_right_x + level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()), next_index_down_y + level_ptr_->GetTileIndexFromPosY(level_ptr_->GetCamPosY()));

	// MOVE LEFT
	if (player_ptr_->getVelocityX() < 0) {
		if ((CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_left_tile_top, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_left_tile_top_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_left_tile_mid, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_left_tile_mid_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_left_tile_down, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_left_tile_down_char) == 0)) {
			player_ptr_->setVelocityX(0);
		}
	}
	// MOVE RIGHT
	if (player_ptr_->getVelocityX() > 0) {
		if ((CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_right_tile_top, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_right_tile_top_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_right_tile_mid, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_right_tile_mid_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_right_tile_down, player_ptr_->getVelocityX()) && level_ptr_->IsTileCharCollidable(next_right_tile_down_char) == 0)) {
			player_ptr_->setVelocityX(0);
		}
	}
	// MOVE UP
	if (player_ptr_->getVelocityY() < 0) {
		if ((CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_top_tile_left, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_top_tile_left_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_top_tile_mid, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_top_tile_mid_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_top_tile_right, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_top_tile_right_char) == 0)) {
			player_ptr_->setVelocityY(0);
		}
	}
	// MOVE DOWN
	if (player_ptr_->getVelocityY() > 0) {
		if ((CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_down_tile_left, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_down_tile_left_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_down_tile_mid, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_down_tile_mid_char) == 0) ||
			(CollisionManager::WillCollideAABB(player_ptr_->getHitBox(), next_down_tile_right, player_ptr_->getVelocityY()) && level_ptr_->IsTileCharCollidable(next_down_tile_right_char) == 0)) {
			player_ptr_->setVelocityY(0);
		}
	}
	/*std::cout << "left top = " << next_index_left_x << " " << index_top_y << " " << next_left_tile_top_char << std::endl;
	std::cout << "left down = " << next_index_left_x << " " << index_down_y << " " << next_left_tile_down_char << std::endl;
	std::cout << "right top = " << next_index_right_x << " " << index_top_y << " " << next_right_tile_top_char << std::endl;
	std::cout << "right down = " << next_index_right_x << " " << index_down_y << " " << next_right_tile_down_char << std::endl;*/
	//std::cout << "player Y = " << player_ptr_->getHitBoxY() << std::endl;
	//std::cout << "tile Y = " << next_right_tile_top->y << std::endl;

	// PRE-PROCESSING
	int new_player_center_x = player_ptr_->getDstCenterX() + player_ptr_->getVelocityX();
	int new_player_pos_x = player_ptr_->getDstX();
	int new_cam_pos_x = level_ptr_->GetCamPosX();
	int new_player_center_y = player_ptr_->getDstCenterY() + player_ptr_->getVelocityY();
	int new_player_pos_y = player_ptr_->getDstY();
	int new_cam_pos_y = level_ptr_->GetCamPosY();

	// MOVE PLAYER IF NOT PAST BOUNDS ("HALF SCREEN"), OTHERWISE MOVE CAM
	//compare cam w/ level max x/y, compare player with screen w/h
	if ((level_ptr_->GetCamPosX() == 0 && new_player_center_x <= Globals::sWindowWidth / 2) ||
		(level_ptr_->GetCamPosX() + Globals::sWindowWidth == level_ptr_->GetLevelMaxPosX() && new_player_center_x >= Globals::sWindowWidth / 2)) //WILL NOT WORK W/ player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() > level_ptr_->GetLevelMaxPosX() - Globals::sWindowWidth / 2
	{
		if (player_ptr_->getHitBoxX() + player_ptr_->getVelocityX() >= 0 && player_ptr_->getHitBoxRightmostX() + player_ptr_->getVelocityX() <= Globals::sWindowWidth) {
			new_player_pos_x += player_ptr_->getVelocityX();
		}
		//player_ptr_->setDstX(player_ptr_->getDstX() + player_ptr_->getVelocityX());
	}
	else {
		new_cam_pos_x += player_ptr_->getVelocityX();
		//level_ptr_->SetCamPosX(level_ptr_->GetCamPosX() + player_ptr_->getVelocityX());
	}

	if ((level_ptr_->GetCamPosY() == 0 && new_player_center_y <= Globals::sWindowHeight / 2) ||
		(level_ptr_->GetCamPosY() + Globals::sWindowHeight == level_ptr_->GetLevelMaxPosY() && new_player_center_y >= Globals::sWindowHeight / 2))
	{
		if (player_ptr_->getHitBoxY() + player_ptr_->getVelocityY() >= 0 && player_ptr_->getHitBoxLowermostY() + player_ptr_->getVelocityY() <= Globals::sWindowHeight) {
			new_player_pos_y += player_ptr_->getVelocityY();
		}
		//player_ptr_->setDstY(player_ptr_->getDstY() + player_ptr_->getVelocityY());
	}
	else {
		new_cam_pos_y += player_ptr_->getVelocityY();
		//level_ptr_->SetCamPosY(level_ptr_->GetCamPosY() + player_ptr_->getVelocityY());
	}

	player_ptr_->setDstXAndHitBox(new_player_pos_x);
	player_ptr_->setDstYAndHitBox(new_player_pos_y);
	level_ptr_->SetCamPosX(new_cam_pos_x);
	level_ptr_->SetCamPosY(new_cam_pos_y);

	//if ((level_ptr_->GetCamPosX() == 0 && new_player_center_x <= Globals::sWindowWidth / 2) ||
	//	(level_ptr_->GetCamPosX() + Globals::sWindowWidth == level_ptr_->GetLevelMaxPosX() && new_player_center_x >= Globals::sWindowWidth / 2) ||
	//	(level_ptr_->GetCamPosY() == 0 && new_player_center_y <= Globals::sWindowHeight / 2) ||
	//	(level_ptr_->GetCamPosY() + Globals::sWindowHeight == level_ptr_->GetLevelMaxPosY() && new_cam_pos_y >= Globals::sWindowHeight / 2))
	//{
	//	player_ptr_->setDstX(player_ptr_->getDstX() + player_ptr_->getVelocityX());
	//	player_ptr_->setDstY(player_ptr_->getDstY() + player_ptr_->getVelocityY());
	//}
	//else {
	//	level_ptr_->SetCamPosX(level_ptr_->GetCamPosX() + player_ptr_->getVelocityX());
	//	level_ptr_->SetCamPosY(level_ptr_->GetCamPosY() + player_ptr_->getVelocityY());
	//}

	//player_ptr_->update();
	level_ptr_->update();

	//std::cout << "PLAYER X = " << player_ptr_->getDstX()<< std::endl;
	//std::cout << "CAM X = " << level_ptr_->GetCamPosX()<< std::endl;
	//std::cout << "CURRTILE X = " << level_ptr_->GetWorldTileIndexFromPosX(level_ptr_->GetCamPosX()) << std::endl;
	//std::cout << "OFFSET Y = " << level_ptr_->GetLevelOffsetY() << std::endl;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour


	level_ptr_->draw(getRenderer());
	player_ptr_->draw(getRenderer());


	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	TheSoundManager::Instance()->freeAllSounds();
	TheTextureManager::Instance()->destroyAllTextures();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

