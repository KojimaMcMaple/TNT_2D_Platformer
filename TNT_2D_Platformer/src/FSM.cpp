#include "FSM.h"
#include "Game.h"

GameState::GameState() 
{
}

void GameState::Render()
{
	SDL_RenderPresent(TheGame::Instance()->getRenderer());
}


void GameState::Resume()
{
}

// PAUSE 
PauseState::PauseState()
{
}

void PauseState::Enter()
{
	std::cout << "Entering Pause..." << std::endl;
}

void PauseState::Update()
{
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_R)) {
		TheGame::Instance()->GetFSM().PopState();
	}
}

void PauseState::Render()
{
	std::cout << "Rendering Pause..." << std::endl;
	TheGame::Instance()->GetFSM().GetStates().front()->Render();
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 50);
	SDL_Rect temp_overlay = { 0,0,Globals::sWindowWidth,Globals::sWindowHeight };
	SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &temp_overlay);
	TheGame::Instance()->GetPauseScreen().draw();
	GameState::Render();
}

void PauseState::Exit()
{
	std::cout << "Exiting Pause..." << std::endl;
}

// RUNNING
RunningState::RunningState()
{
	TheGame::Instance()->createGameObjects();
}

void RunningState::Enter()
{
	std::cout << "Entering Game..." << std::endl;
	TheTextureManager::Instance()->load("../Assets/textures/Arrow.png",
		"arrow", TheGame::Instance()->getRenderer());

	TheSoundManager::Instance()->load("../assets/audio/SFX_PLAYER_ATK.mp3", SFX_PLAYER_ATK, SOUND_SFX);
	TheSoundManager::Instance()->load("../assets/audio/SFX_PLAYER_ASSAULTED.mp3", SFX_PLAYER_ASSAULTED, SOUND_SFX);
	TheSoundManager::Instance()->load("../assets/audio/SFX_SKELETON_ATK.mp3", SFX_SKELETON_ATK, SOUND_SFX);
	TheSoundManager::Instance()->load("../assets/audio/SFX_PLAYER_ATKRANGED.mp3", SFX_PLAYER_ATKRANGED, SOUND_SFX);
	TheSoundManager::Instance()->load("../assets/audio/SFX_SKELETON_ASSAULTED.mp3", SFX_SKELETON_ASSAULTED, SOUND_SFX);

}

void RunningState::Update()
{
	TheGame::Instance()->UpdateGameObjects();
	
	if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_P)) {
		TheGame::Instance()->GetFSM().PushState(new PauseState());
	}
	else if (TheGame::Instance()->isKeyDown(SDL_SCANCODE_X)) {
		TheGame::Instance()->GetFSM().ChangeState(new TitleState());
	}

}

void RunningState::Render()
{
	//std::cout << "Rendering Game..." << std::endl;
	SDL_RenderClear(TheGame::Instance()->getRenderer()); // clear the renderer to the draw colour
	TheGame::Instance()->RenderGameObjects();

	if (dynamic_cast<RunningState*>(TheGame::Instance()->GetFSM().GetStates().back())) {
		GameState::Render();
	}
}

void RunningState::Exit()
{
	std::cout << "Exiting Game..." << std::endl;
}

void RunningState::Resume()
{
}

// TITLE
TitleState::TitleState()
{
	this->_is_config = false;	
}

void TitleState::Enter()
{
	std::cout << "Entering Title..." << std::endl;
	if (!this->_t_menu) this->_t_menu = new TitleMenu();
	if (!this->_t_config) this->_t_config = new ConfigMenu();
	this->_t_menu->GetText()->SetUIState(UIState::ACTIVATING);
}

void TitleState::Update()
{	
	// Handle input with each title menu state
	if (_is_config) { // If open Options Menu
		if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_RETURN))
			this->_t_config->ExecuteCmd();
		if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_UP))
		{
			this->_t_config->_c_cursor_pos--;
			if (this->_t_config->_c_cursor_pos < 0) this->_t_config->_c_cursor_pos = 5;
			else if (this->_t_config->_c_cursor_pos == 1) this->_t_config->_c_cursor_pos--;

			this->_t_config->SetCursorPos();
		}
		if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_DOWN))
		{
			this->_t_config->_c_cursor_pos++;
			if (this->_t_config->_c_cursor_pos > 5) this->_t_config->_c_cursor_pos = 0;
			else if (this->_t_config->_c_cursor_pos == 1) this->_t_config->_c_cursor_pos++;
		
			this->_t_config->SetCursorPos();
		}

		if (TheGame::Instance()->GetController()->isHold(SDL_SCANCODE_N))
			this->_is_config = false;
		return;
	}
	else {
		switch (this->_t_menu->GetMenuState())
		{
			case TitleMenuState::TITLE:
			{
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_RETURN))
					this->_t_menu->SetMenuState(TitleMenuState::NEWGAME);
				break;
			}
			case TitleMenuState::NEWGAME:
			{
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_RETURN))
					TheGame::Instance()->GetFSM().ChangeState(new RunningState());
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_UP))
					this->_t_menu->SetMenuState(TitleMenuState::QUIT);
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_DOWN))
					this->_t_menu->SetMenuState(TitleMenuState::CONFIG);
				break;
			}
			case TitleMenuState::CONFIG:
			{
				// TODO(@nghialam): Option UI or State
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_RETURN))
					this->_is_config = true;
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_UP))
					this->_t_menu->SetMenuState(TitleMenuState::NEWGAME);
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_DOWN))
					this->_t_menu->SetMenuState(TitleMenuState::QUIT);
				break;
			}
			case TitleMenuState::QUIT:
			{
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_RETURN))
					TheGame::Instance()->setRunning(false);
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_UP))
					this->_t_menu->SetMenuState(TitleMenuState::CONFIG);
				if (TheGame::Instance()->GetController()->isPressed(SDL_SCANCODE_DOWN))
					this->_t_menu->SetMenuState(TitleMenuState::NEWGAME);
				break;
			}
			return;
		}
	}
}

void TitleState::Render()
{
	SDL_RenderClear(TheGame::Instance()->getRenderer()); // clear the renderer to the draw colour
	
	TheGame::Instance()->GetTitleScreen().draw();
	if (_is_config)
	{
		this->_t_config->draw();
	}
	else
	{
		this->_t_menu->draw();
	}
	GameState::Render();
}

void TitleState::Exit()
{
	std::cout << "Exiting Title..." << std::endl;
}

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::Update()
{
	if (!states_.empty()) {
		states_.back()->Update();
	}
}

void FSM::Render()
{
	if (!states_.empty()) {
		states_.back()->Render();
	}
}

void FSM::ChangeState(GameState* state_ptr)
{
	if (!states_.empty()) {
		states_.back()->Exit(); //invoke Exit() of curr state
		delete states_.back(); //deallocate curr state
		states_.back() = nullptr;
		states_.pop_back();
	}
	PushState(state_ptr);

	//state_ptr->Enter();
	//states_.push_back(state_ptr);

	//states_.push_back(state_ptr);
	//states_.back()->Enter();
}

void FSM::PushState(GameState* state_ptr)
{
	state_ptr->Enter();
	states_.push_back(state_ptr);
}

void FSM::PopState()
{
	if (!states_.empty()) {
		states_.back()->Exit(); //invoke Exit() of curr state
		delete states_.back(); //deallocate curr state
		states_.back() = nullptr;
		states_.pop_back();
	}
	states_.back()->Resume();
}

void FSM::Clean()
{
	while (!states_.empty()) {
		states_.back()->Exit(); //invoke Exit() of curr state
		delete states_.back(); //deallocate curr state
		states_.back() = nullptr;
		states_.pop_back();
	}
}

std::vector<GameState*>& FSM::GetStates()
{
	// TODO: insert return statement here
	return states_;
}