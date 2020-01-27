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

glm::vec2 Game::getMousePosition()
{
	return m_mousePosition;
}

void Game::createGameObjects()
{
	level_ptr_ = new Level(getRenderer());
	level_ptr_->SetLevelWidth(64);
	level_ptr_->SetLevelHeight(16);
	std::string level_raw_str = "";
	level_raw_str += "................................................................";
	level_raw_str += "................................................................";
	level_raw_str += ".......ooooo....................................................";
	level_raw_str += "........ooo.....................................................";
	level_raw_str += ".......................########.................................";
	level_raw_str += ".....BB?BBBB?BB.......###..............#.#......................";
	level_raw_str += "....................###................#.#......................";
	level_raw_str += "...................####.........................................";
	level_raw_str += "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG.##############.....########";
	level_raw_str += "...................................#.#...............###........";
	level_raw_str += "........................############.#............###...........";
	level_raw_str += "........................#............#.........###..............";
	level_raw_str += "........................#.############......###.................";
	level_raw_str += "........................#................###....................";
	level_raw_str += "........................#################.......................";
	level_raw_str += "................................................................";
	level_ptr_->LoadLevel(level_raw_str);

	player_ptr_ = new Player(getRenderer());
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

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

	level_ptr_->draw(getRenderer());
	player_ptr_->draw(getRenderer());
	

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	// PROCESSING, HAPPENS WHEN KEYS ARE HELD DOWN
	if (s_pInstance->isKeyDown(SDL_SCANCODE_W) || s_pInstance->isKeyDown(SDL_SCANCODE_UP)) {
		player_ptr_->setDstY(player_ptr_->getDstY() - player_ptr_->getVelocity());
		level_ptr_->SetCamPosY(player_ptr_->getDstY());
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_S) || s_pInstance->isKeyDown(SDL_SCANCODE_DOWN)) {
		player_ptr_->setDstY(player_ptr_->getDstY() + player_ptr_->getVelocity());
		level_ptr_->SetCamPosY(player_ptr_->getDstY());
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_A) || s_pInstance->isKeyDown(SDL_SCANCODE_LEFT)) {
		player_ptr_->setDstX(player_ptr_->getDstX() - player_ptr_->getVelocity());
		level_ptr_->SetCamPosX(player_ptr_->getDstX());
	}
	if (s_pInstance->isKeyDown(SDL_SCANCODE_D) || s_pInstance->isKeyDown(SDL_SCANCODE_RIGHT)) {
		player_ptr_->setDstX(player_ptr_->getDstX() + player_ptr_->getVelocity());
		level_ptr_->SetCamPosX(player_ptr_->getDstX());
	}
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

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	TheSoundManager::Instance()->freeAllSounds();
	TheTextureManager::Instance()->destroyAllTextures();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
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