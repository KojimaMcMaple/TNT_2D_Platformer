#include "Game.h"
#include "Util.h"

Game* Game::s_pInstance = 0;

Game::Game()
{
	this->m_bRunning = true;
}

Game::~Game()
{
}

glm::vec2 Game::getTargetPosition()
{
	return glm::vec2(0,0);
}

Uint32 Game::getFrames() const
{
	return m_frames;
}

SDL_Renderer* Game::getRenderer()
{
	return m_pRenderer;
}

FSM& Game::GetFSM()
{
	return *fsm_;
}

WindowManager* Game::GetWindowManager()
{
	return m_wm;
}

Controller* Game::GetController()
{
	return this->m_controller;
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

Camera* Game::GetCamera()
{
	// TODO: insert return statement here
	return camera_ptr_;
}

Level* Game::GetLevel()
{
	return level_ptr_;
}

void Game::setFrames(Uint32 frames)
{
	m_frames = frames;
}

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

void Game::createGameObjects()
{
	title_screen_ptr_ = new UI("title", "../Assets/textures/bg_4x3.png", 0, 0, Globals::sWindowWidth / 2, Globals::sWindowHeight / 2, 0, 0, Globals::sWindowWidth, Globals::sWindowHeight);
	pause_screen_ptr_ = new UI("pause", "../Assets/textures/Pause_Screen.png", 0, 0, Globals::sWindowWidth / 2, Globals::sWindowHeight / 2, 0, 0, Globals::sWindowWidth, Globals::sWindowHeight);

	level_ptr_ = new Level();
	level_ptr_->LoadLevel(LevelId::CHURCH);

	player_ptr_ = new Player();
	player_ptr_->SetWorldXAndHitBox(1 * level_ptr_->GetLevelTileWidth());
	player_ptr_->SetWorldYAndHitBox(6 * level_ptr_->GetLevelTileHeight());

	enemy_list_.clear();
	enemy_list_.resize(0);
	enemy_list_.shrink_to_fit();
	enemy_list_.push_back(new Enemy(SKELETON_SWORD, 10 * level_ptr_->GetLevelTileWidth(), 6 * level_ptr_->GetLevelTileHeight()));
	//std::cout << enemy_list_.back()->GetWorldRect()->x << std::endl;

	// CENTER CAM TO PLAYER
	camera_ptr_ = new Camera();
	camera_ptr_->RefocusCamera(player_ptr_, level_ptr_);

	level_ptr_->SetCamPosX(camera_ptr_->GetWorldRect()->x);
	level_ptr_->SetCamPosY(camera_ptr_->GetWorldRect()->y);
}

void Game::CheckCollision()
{
	// PLAYER COLLI
	level_ptr_->CheckLevelCollision(player_ptr_);
	
	// ENEMY COLLI
	for (int i = 0; i < enemy_list_.size(); i++) {
		Enemy* enemy = enemy_list_[i];
		level_ptr_->CheckLevelCollision(enemy);
		if (player_ptr_->IsAtkHitBoxActive() && SDL_HasIntersection(player_ptr_->GetAtkHitBox(), enemy->getHitBox())) {
			enemy->setAnimState(AnimState::ENEMY_HIT);
		}
	}
}

void Game::UpdateGameObjects()
{
	// INPUT HANDLE
	if (s_pInstance->GetController()->isHold(SDL_SCANCODE_A) || s_pInstance->GetController()->isHold(SDL_SCANCODE_LEFT)) {
		player_ptr_->setMoveDirection(-1);
		player_ptr_->MoveX();
		if (player_ptr_->IsGrounded()) {
			player_ptr_->setAnimState(AnimState::RUN);
		}
	}
	if (s_pInstance->GetController()->isHold(SDL_SCANCODE_D) || s_pInstance->GetController()->isHold(SDL_SCANCODE_RIGHT)) {
		player_ptr_->setMoveDirection(1);
		player_ptr_->MoveX();
		if (player_ptr_->IsGrounded()) {
			player_ptr_->setAnimState(AnimState::RUN);
		}
	}
	if (s_pInstance->GetController()->isPressed(SDL_SCANCODE_SPACE) && player_ptr_->IsGrounded()) {
		player_ptr_->setAccelerationY(-Globals::sJumpForce);
		player_ptr_->SetGrounded(false);
		player_ptr_->setAnimState(AnimState::JUMP);
	}
	if (s_pInstance->GetController()->isHold(SDL_SCANCODE_RSHIFT) && player_ptr_->IsGrounded()) {
		player_ptr_->setAnimState(AnimState::ATTACK);
	}

	// POST PROCESSING
	// PLAYER
	if (player_ptr_->getAnimState() == AnimState::ATTACK) {
		player_ptr_->StopX();
		if (player_ptr_->IsAtkHitBoxActive()) {
			if (player_ptr_->getMoveDirection() == 1) { //facing right
				player_ptr_->SetAtkHitBoxX(player_ptr_->getHitBoxRightmostX());
				player_ptr_->SetAtkHitBoxY(player_ptr_->getHitBoxY());
			}
			else { //facing left
				player_ptr_->SetAtkHitBoxX(player_ptr_->getHitBoxX() - player_ptr_->GetAtkHitBox()->w);
				player_ptr_->SetAtkHitBoxY(player_ptr_->getHitBoxY());
			}
		}
		if (player_ptr_->HasEndedAnimation()) { //anim ended, GetNumFrames()-1 WILL SKIP THE LAST FRAME OF ANIM
			player_ptr_->setAnimState(AnimState::IDLE);
		}
	}

	if (player_ptr_->getAnimState() != AnimState::ATTACK) { //force atk hit box to turn off 
		player_ptr_->SetAtkHitBoxActive(false);
	}

	player_ptr_->update();
	player_ptr_->setAccelerationY(0);

	if (!player_ptr_->IsGrounded() && player_ptr_->getVelocityY() > 0) {
		player_ptr_->setAnimState(AnimState::FALL);
	}

	CheckCollision();

	if (player_ptr_->IsGrounded() && player_ptr_->getAnimState() != AnimState::RUN && player_ptr_->getAnimState() != AnimState::ATTACK) {
		player_ptr_->setAnimState(AnimState::IDLE);
	}

	// ENEMIES
	for (int i = 0; i < enemy_list_.size(); i++) {
		enemy_list_[i]->update(); //implement enemy behaviors in Enemy class, since there is no control input handling
	}

	// CAMERA
	camera_ptr_->RefocusCamera(player_ptr_, level_ptr_);
	
	// LEVEL
	level_ptr_->SetCamPosX(camera_ptr_->GetWorldRect()->x);
	level_ptr_->SetCamPosY(camera_ptr_->GetWorldRect()->y);
	level_ptr_->update();

	
}

void Game::RenderGameObjects()
{
	level_ptr_->draw();
	for (int i = 0; i < enemy_list_.size(); i++) {
		camera_ptr_->draw(enemy_list_[i]);
	}
	camera_ptr_->draw(player_ptr_);
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;
		
		m_wm = new WindowManager(title, xpos, ypos, width, height, fullscreen);
		m_controller = new Controller();
		// if succeeded create our window
		m_pWindow = m_wm->GetMainWindow();

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
				player_ptr_->StopX();
				if (player_ptr_->IsGrounded()) {
					player_ptr_->setAnimState(AnimState::IDLE);
				}
			}
			m_controller->handleKeyboardEvent(event);
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
	delete m_controller;
	delete m_wm;
	delete fsm_;
	//fsm_ = nullptr;

	TheSoundManager::Instance()->freeAllSounds();
	TheTextureManager::Instance()->destroyAllTextures();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

