#include "Game.h"
#include "Util.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	SetJumpKeyPressable(true);
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

FSM& Game::GetFSM()
{
	return *fsm_;
}

int Game::GetOffsetPositionX()
{
	return offset_position_x_;
}

int Game::GetOffsetPositionY()
{
	return offset_position_y_;
}

bool Game::IsJumpKeyPressable()
{
	return is_jump_key_pressable_;
}

UI& Game::GetTitleScreen()
{
	// TODO: insert return statement here
	return *title_screen_ptr_;
}

UI& Game::GetPauseScreen()
{
	// TODO: insert return statement here
	return *pause_screen_ptr_;
}

void Game::SetOffsetPositionX(int x_distance)
{
	offset_position_x_ = x_distance;
}

void Game::SetOffsetPositionY(int y_distance)
{
	offset_position_y_ = y_distance;
}

void Game::SetJumpKeyPressable(bool toggle)
{
	is_jump_key_pressable_ = toggle;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

void Game::createGameObjects()
{
	title_screen_ptr_ = new UI("title", "../Assets/textures/Title_Screen.png", 0, 0, Globals::sWindowWidth / 2, Globals::sWindowHeight / 2, 0, 0, Globals::sWindowWidth, Globals::sWindowHeight);
	pause_screen_ptr_ = new UI("pause", "../Assets/textures/Pause_Screen.png", 0, 0, Globals::sWindowWidth / 2, Globals::sWindowHeight / 2, 0, 0, Globals::sWindowWidth, Globals::sWindowHeight);

	level_ptr_ = new Level();
	level_ptr_->LoadLevel("church");

	player_ptr_ = new Player();
	player_ptr_->setDstXAndHitBox(4 * level_ptr_->GetLevelTileWidth() + level_ptr_->GetLevelTileWidth() / 2 - player_ptr_->getDstW() / 2);
	player_ptr_->setDstYAndHitBox(4 * level_ptr_->GetLevelTileHeight() + level_ptr_->GetLevelTileHeight() / 2 - player_ptr_->getDstH() / 2);

	// CENTER CAM TO PLAYER
	camera_ptr_ = new Camera();
	camera_ptr_->RefocusCamera(player_ptr_, level_ptr_);

	level_ptr_->SetCamPosX(camera_ptr_->GetWorldRect()->x);
	level_ptr_->SetCamPosY(camera_ptr_->GetWorldRect()->y);
}

void Game::CheckCollisionTest()
{
	//int player_tile_index_x = level_ptr_->GetTileIndexFromPosX(player_ptr_->getHitBoxX() + level_ptr_->GetTileOffsetX()); //offset to handle screen-scrolling, fixed the issue of player not mapped correctly to an offseted tile
	//int player_tile_index_y = level_ptr_->GetTileIndexFromPosY(player_ptr_->getHitBoxY() + level_ptr_->GetTileOffsetY());

	//for (int row = (player_tile_index_y < 0 ? 0 : player_tile_index_y); row < ((player_tile_index_y + 3) > level_ptr_->GetVisibleTilesNumOfRows() ? level_ptr_->GetVisibleTilesNumOfRows() : (player_tile_index_y + 3)); row++)
	//{
	//	for (int col = (player_tile_index_x < 0 ? 0 : player_tile_index_x); col < ((player_tile_index_x + 2) > level_ptr_->GetVisibleTilesNumOfColumns() ? level_ptr_->GetVisibleTilesNumOfColumns() : (player_tile_index_x + 2)); col++)
	//	{
	//		if (level_ptr_->GetVisibleTileObj(col,row) != nullptr && SDL_HasIntersection(player_ptr_->getDst(), level_ptr_->GetVisibleTileObj(row, col)))
	//		{
	//			if ((player_ptr_->getDst()->y + player_ptr_->getDst()->h) - player_ptr_->getVelocityY() <= level_ptr_->GetVisibleTileObj(row, col)->y)
	//			{ // Collision from top.
	//				player_ptr_->SetGrounded(true);
	//				player_ptr_->setVelocityY(0.0); // Stop the player from moving vertically. We aren't modifying gravity.
	//				player_ptr_->setDstY(level_ptr_->GetVisibleTileObj(row, col)->y - player_ptr_->getDst()->h);
	//			}
	//			else if (player_ptr_->getDst()->y - player_ptr_->getVelocityY() >= level_ptr_->GetVisibleTileObj(row, col)->y + level_ptr_->GetVisibleTileObj(col,row)->h)
	//			{ // Collision from bottom.
	//				player_ptr_->setVelocityY(0.0); // Stop the player from moving vertically. We aren't modifying gravity.
	//				player_ptr_->setDstY(level_ptr_->GetVisibleTileObj(col,row)->y + level_ptr_->GetVisibleTileObj(col,row)->h);
	//			}
	//			else if ((player_ptr_->getDst()->x + player_ptr_->getDst()->w) - player_ptr_->getVelocityX() <= level_ptr_->GetVisibleTileObj(col,row)->x)
	//			{ // Collision from left.
	//				player_ptr_->setVelocityX(0.0); // Stop the player from moving horizontally.
	//				player_ptr_->setDstX(level_ptr_->GetVisibleTileObj(col,row)->x - player_ptr_->getDst()->w);
	//			}
	//			else if (player_ptr_->getDst()->x - player_ptr_->getVelocityX() >= level_ptr_->GetVisibleTileObj(col,row)->x + level_ptr_->GetVisibleTileObj(col,row)->w)
	//			{ // Collision from right.
	//				player_ptr_->setVelocityX(0.0); // Stop the player from moving horizontally.
	//				player_ptr_->setDstX(level_ptr_->GetVisibleTileObj(col,row)->x + level_ptr_->GetVisibleTileObj(col,row)->w);
	//			}
	//			//break;
	//		}
	//	}
	//}

	//// PRE-PROCESSING
	//int new_player_center_x = player_ptr_->getDstCenterX() + player_ptr_->getVelocityX();
	//int new_player_pos_x = player_ptr_->getDstX();
	//int new_cam_pos_x = level_ptr_->GetCamPosX();
	//int new_player_center_y = player_ptr_->getDstCenterY() + player_ptr_->getVelocityY();
	//int new_player_pos_y = player_ptr_->getDstY();
	//int new_cam_pos_y = level_ptr_->GetCamPosY();

	//// MOVE PLAYER IF NOT PAST BOUNDS ("HALF SCREEN"), OTHERWISE MOVE CAM
	////compare cam w/ level max x/y, compare player with screen w/h
	//if ((level_ptr_->GetCamPosX() == 0 && new_player_center_x <= Globals::sWindowWidth / 2) ||
	//	(level_ptr_->GetCamPosX() + Globals::sWindowWidth == level_ptr_->GetLevelMaxPosX() && new_player_center_x >= Globals::sWindowWidth / 2)) //WILL NOT WORK W/ player_ptr_->getDstCenterX() + player_ptr_->getVelocityX() > level_ptr_->GetLevelMaxPosX() - Globals::sWindowWidth / 2
	//{
	//	if (player_ptr_->getHitBoxX() + player_ptr_->getVelocityX() >= 0 && player_ptr_->getHitBoxRightmostX() + player_ptr_->getVelocityX() <= Globals::sWindowWidth) {
	//		new_player_pos_x += player_ptr_->getVelocityX();
	//	}
	//	//player_ptr_->setDstX(player_ptr_->getDstX() + player_ptr_->getVelocityX());
	//}
	//else {
	//	new_cam_pos_x += player_ptr_->getVelocityX();
	//	//level_ptr_->SetCamPosX(level_ptr_->GetCamPosX() + player_ptr_->getVelocityX());
	//}

	//if (player_ptr_->getHitBoxY() + player_ptr_->getVelocityY() >= 0 && player_ptr_->getHitBoxLowermostY() + player_ptr_->getVelocityY() <= Globals::sWindowHeight) {
	//	new_player_pos_y += player_ptr_->getVelocityY();
	//}

	////if ((level_ptr_->GetCamPosY() == 0 && new_player_center_y <= Globals::sWindowHeight / 2) ||
	////	(level_ptr_->GetCamPosY() + Globals::sWindowHeight == level_ptr_->GetLevelMaxPosY() && new_player_center_y >= Globals::sWindowHeight / 2))
	////{
	////	if (player_ptr_->getHitBoxY() + player_ptr_->getVelocityY() >= 0 && player_ptr_->getHitBoxLowermostY() + player_ptr_->getVelocityY() <= Globals::sWindowHeight) {
	////		new_player_pos_y += player_ptr_->getVelocityY();
	////	}
	////	//player_ptr_->setDstY(player_ptr_->getDstY() + player_ptr_->getVelocityY());
	////}
	////else {
	////	new_cam_pos_y += player_ptr_->getVelocityY();
	////	//level_ptr_->SetCamPosY(level_ptr_->GetCamPosY() + player_ptr_->getVelocityY());
	////}

	//player_ptr_->setDstXAndHitBox(new_player_pos_x);
	//player_ptr_->setDstYAndHitBox(new_player_pos_y);
	//level_ptr_->SetCamPosX(new_cam_pos_x);
	//level_ptr_->SetCamPosY(new_cam_pos_y);
}

void Game::UpdateGameObjects()
{
	if (s_pInstance->isKeyDown(SDL_SCANCODE_A) || s_pInstance->isKeyDown(SDL_SCANCODE_LEFT)) {
		player_ptr_->setMoveDirection(-1);
		player_ptr_->MoveX();
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_D) || s_pInstance->isKeyDown(SDL_SCANCODE_RIGHT)) {
		player_ptr_->setMoveDirection(1);
		player_ptr_->MoveX();
	}
	//if (s_pInstance->isKeyDown(SDL_SCANCODE_SPACE) && IsJumpKeyPressable() && player_ptr_->IsGrounded()) {
	if (s_pInstance->isKeyDown(SDL_SCANCODE_SPACE) && IsJumpKeyPressable()) {
		//SetJumpKeyPressable(false);
		player_ptr_->setAccelerationY(-Globals::sJumpForce);
		//player_ptr_->SetGrounded(false);
	}

	player_ptr_->update();
	player_ptr_->setAccelerationY(0);
	//std::cout << "vel Y = " << player_ptr_->getVelocityY() << std::endl;

	//CheckCollisionTest();

	camera_ptr_->RefocusCamera(player_ptr_, level_ptr_);
	
	level_ptr_->SetCamPosX(camera_ptr_->GetWorldRect()->x);
	level_ptr_->SetCamPosY(camera_ptr_->GetWorldRect()->y);
	level_ptr_->update();
}

void Game::RenderGameObjects()
{
	level_ptr_->draw();
	player_ptr_->draw();
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
	fsm_ = new FSM();
	fsm_->ChangeState(new TitleState());
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
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
				player_ptr_->setAccelerationX(0);
			}
			if (event.key.keysym.sym == SDLK_SPACE) {
				SetJumpKeyPressable(true);
			}
			break;
		default:
			break;
		}
	}

	// PROCESSING, HAPPENS WHEN KEYS ARE HELD DOWN
	//if (s_pInstance->isKeyDown(SDL_SCANCODE_W) || s_pInstance->isKeyDown(SDL_SCANCODE_UP)) {
	//	player_ptr_->setVelocityY(-6);
	//}
	//if (s_pInstance->isKeyDown(SDL_SCANCODE_S) || s_pInstance->isKeyDown(SDL_SCANCODE_DOWN)) {
	//	player_ptr_->setVelocityY(6);
	//}
}

void Game::update()
{
	GetFSM().Update();
}

void Game::render()
{
	GetFSM().Render();
	
	//SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour


	//level_ptr_->draw();
	//player_ptr_->draw();


	//SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;
	//fsm_->Clean();
	GetFSM().Clean();
	delete fsm_;
	//fsm_ = nullptr;

	TheSoundManager::Instance()->freeAllSounds();
	TheTextureManager::Instance()->destroyAllTextures();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

