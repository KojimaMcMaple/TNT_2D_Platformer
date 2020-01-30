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
	level_ptr_ = new Level();
	level_ptr_->LoadLevel(getRenderer(), "church");

	player_ptr_ = new Player(getRenderer());
	player_ptr_->setDstX(1 * level_ptr_->GetTileWidth() + level_ptr_->GetTileWidth() / 2 - player_ptr_->getDstW() / 2);
	player_ptr_->setDstY(1 * level_ptr_->GetTileHeight() + level_ptr_->GetTileHeight() / 2 - player_ptr_->getDstH() / 2);

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

	//if (level_ptr_->GetCamPosX() == 0) {
	//	std::cout << "(1) IS TRUE" << std::endl;
	//}
	//if (player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() <= Globals::sWindowWidth / 2) {
	//	std::cout << "(2) IS TRUE" << std::endl;
	//}
	//if (level_ptr_->GetCamPosX() + Globals::sWindowWidth == level_ptr_->GetLevelMaxPosX()) {
	//	std::cout << "(3) IS TRUE" << std::endl;
	//}
	//if (player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() >= Globals::sWindowWidth / 2) {
	//	std::cout << "(4) IS TRUE" << std::endl;
	//}
	////else {
	////	std::cout << "(4) IS FALSE WITH " << player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() << " " << level_ptr_->GetLevelMaxPosX() - Globals::sWindowWidth / 2 << std::endl;
	////}
	//if (player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() > Globals::sWindowWidth / 2) {
	//	std::cout << "(5) IS TRUE" << std::endl;
	//}
	//if (player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() < level_ptr_->GetLevelMaxPosX() - Globals::sWindowWidth / 2) {
	//	std::cout << "(6) IS TRUE" << std::endl;
	//}

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
		if (player_ptr_->getCollideBoxX() + player_ptr_->getVelocityX() >= 0 && player_ptr_->getCollideBoxRightmostX() + player_ptr_->getVelocityX() <= Globals::sWindowWidth) {
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
		if (player_ptr_->getCollideBoxY() + player_ptr_->getVelocityY() >= 0 && player_ptr_->getCollideBoxLowermostY() + player_ptr_->getVelocityY() <= Globals::sWindowHeight) {
			new_player_pos_y += player_ptr_->getVelocityY();
		}
		//player_ptr_->setDstY(player_ptr_->getDstY() + player_ptr_->getVelocityY());
	}
	else {
		new_cam_pos_y += player_ptr_->getVelocityY();
		//level_ptr_->SetCamPosY(level_ptr_->GetCamPosY() + player_ptr_->getVelocityY());
	}



	// COLLISION CHECK
	//0=solid block, 1=air/background, 2=consummables
	// LEFT
	if (player_ptr_->getVelocityX() <= 0) { \
		if (level_ptr_->IsTileCharCollidable(level_ptr_->GetTileIndexFromPosX(new_player_center_x) - 1) == 0) {
			player_ptr_->setDstX(new_player_dst_x);
		}
		
	}

	player_ptr_->setDstX(new_player_pos_x);
	player_ptr_->setDstY(new_player_pos_y);
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

	player_ptr_->update();

	//std::cout << "PLAYER X = " << player_ptr_->getDstX()<< std::endl;
	//std::cout << "CAM X = " << level_ptr_->GetCamPosX()<< std::endl;
	//std::cout << "CURRTILE X = " << level_ptr_->GetTileIndexFromPosX(level_ptr_->GetCamPosX()) << std::endl;
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

