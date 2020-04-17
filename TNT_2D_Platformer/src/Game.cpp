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

void Game::setFrames(Uint32 frames)
{
	m_frames = frames;
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
	level_ptr_->LoadLevel(LevelId::CHURCH);

	player_ptr_ = new Player();
	player_ptr_->SetWorldXAndHitBox(11 * level_ptr_->GetLevelTileWidth());
	player_ptr_->SetWorldYAndHitBox(18 * level_ptr_->GetLevelTileHeight());

	enemy_list_.clear();
	enemy_list_.resize(0);
	enemy_list_.shrink_to_fit();
	enemy_list_.push_back(new Enemy(SKELETON_SWORD, 24 * level_ptr_->GetLevelTileWidth(), 25 * level_ptr_->GetLevelTileHeight()));
	enemy_list_.push_back(new Enemy(SKELETON_SWORD, 8 * level_ptr_->GetLevelTileWidth(), 14 * level_ptr_->GetLevelTileHeight()));
	enemy_list_.push_back(new Enemy(SKELETON_SWORD, 11 * level_ptr_->GetLevelTileWidth(), 5 * level_ptr_->GetLevelTileHeight()));
	enemy_list_.push_back(new Enemy(SKELETON_SWORD, 30 * level_ptr_->GetLevelTileWidth(), 5 * level_ptr_->GetLevelTileHeight()));
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
		//if player still attacking + enemy not dead + SDL_HasIntersection
		if (player_ptr_->IsAtkHitBoxActive() && enemy->getAnimState() != AnimState::DEATH && SDL_HasIntersection(player_ptr_->GetAtkHitBox(), enemy->getHitBox())) {
			if (enemy->getAnimState() != AnimState::ASSAULTED) {
				enemy->SetHP(enemy->GetHP() - player_ptr_->GetAtkPower());
			}
			enemy->setAnimState(AnimState::ASSAULTED);
		}
	}
}

void Game::UpdateGameObjects()
{
	// INPUT HANDLE
	if (s_pInstance->isKeyDown(SDL_SCANCODE_A) || s_pInstance->isKeyDown(SDL_SCANCODE_LEFT)) {
		player_ptr_->setMoveDirection(-1);
		player_ptr_->MoveX();
		if (player_ptr_->IsGrounded()) {
			player_ptr_->setAnimState(AnimState::RUN);
		}
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_D) || s_pInstance->isKeyDown(SDL_SCANCODE_RIGHT)) {
		player_ptr_->setMoveDirection(1);
		player_ptr_->MoveX();
		if (player_ptr_->IsGrounded()) {
			player_ptr_->setAnimState(AnimState::RUN);
		}
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_SPACE) && IsJumpKeyPressable() && player_ptr_->IsGrounded()) {
		SetJumpKeyPressable(false);
		player_ptr_->setAccelerationY(-Globals::sJumpForce);
		player_ptr_->SetGrounded(false);
		player_ptr_->setAnimState(AnimState::JUMP);
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_K) && player_ptr_->IsGrounded()) {
		player_ptr_->setAnimState(AnimState::ATTACK);
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_L) && player_ptr_->IsGrounded()) {
		player_ptr_->setAnimState(AnimState::ATTACK_RANGED);
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
	else {
		player_ptr_->SetAtkHitBoxActive(false); //force atk hit box to turn off 
	}
	if (player_ptr_->getAnimState() == AnimState::ATTACK_RANGED) {
		if (player_ptr_->HasEndedAnimation()) { //anim ended and fire an arrow
			int x, y;
			if (player_ptr_->getMoveDirection() == 1)
			{
				x = player_ptr_->GetWorldRect()->x + 29 * 3;
				y = player_ptr_->GetWorldRect()->y + 22 * 3;
			}
			else
			{
				x = player_ptr_->GetWorldRect()->x + 22 * 3;
				y = player_ptr_->GetWorldRect()->y + 22 * 3;
			}
			m_pArrowVec.push_back(new Arrow(x, y, player_ptr_->getMoveDirection()));
			player_ptr_->setAnimState(AnimState::IDLE);
		}
	}
	//if (!player_ptr_->IsGrounded() && player_ptr_->getVelocityY() > 0) {
	if (player_ptr_->getVelocityY() > 2) { //natural falling
		player_ptr_->setAnimState(AnimState::FALL);
	}
	player_ptr_->update();
	player_ptr_->setAccelerationY(0);

	// PLAYER'S ARROWS
	for (int i = 0; i < (int)m_pArrowVec.size(); i++)
	{
		m_pArrowVec[i]->update();
		// TO UPDATE DEALLOCATE THE ARROWS OUT OF BOUNDS

	}
	
	CheckCollision();

	if (player_ptr_->IsGrounded() 
		&& player_ptr_->getAnimState() != AnimState::RUN 
		&& player_ptr_->getAnimState() != AnimState::ATTACK
		&& player_ptr_->getAnimState() != AnimState::ATTACK_RANGED) {
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
	for (int i = 0; i < (int)m_pArrowVec.size(); i++) {
		camera_ptr_->draw(m_pArrowVec[i]);
	}	
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
				player_ptr_->StopX();
				if (player_ptr_->IsGrounded()) {
					player_ptr_->setAnimState(AnimState::IDLE);
				}
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

