#include "Config.h"
#include "..\Game.h"

ConfigMenu::ConfigMenu()
{
	// Setup Texture
	setTextureId("configmenu");
	TheTextureManager::Instance()->load("../Assets/textures/config.png", getTextureId(), TheGame::Instance()->getRenderer());
	
	// Setup other elements
	this->_c_fullscreen = new ConfigFullScreen();
	this->_c_ratiotext = new ConfigRatioText();
	this->_c_4x3 = new Config_4x3();
	this->_c_1x1 = new Config_1x1();
	this->_c_16x9 = new Config_16x9();
	this->_c_21x9 = new Config_21x9();
	this->_c_tick_ratio = new ConfigTick();
	this->_c_tick_fullscreen = new ConfigTick();
	this->_c_cursor = new ConfigChosen();
	
	this->_c_cursor_pos = 0;

	// Setup Position
	SetConfigPos();

	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

ConfigMenu::~ConfigMenu()
{
}

void ConfigMenu::SetConfigPos()
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = Globals::sWindowWidth / 2 - (TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale) / 2;
	int _dst_y = Globals::sWindowHeight / 2 - (TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale) / 2;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);

	int _offset_header = 20 * Globals::sGuiScale;
	int _offset_left = 10 * Globals::sGuiScale;
	int _line_height = TheTextureManager::Instance()->getTextureSize(this->_c_fullscreen->getTextureId())[1] * Globals::sGuiScale;

	this->_c_fullscreen->SetFullScreenPos(_dst_x + _offset_left, _dst_y + _offset_header);
	this->_c_ratiotext->SetRatioTextPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height);
	this->_c_4x3->Set4x3Pos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height*2);
	this->_c_1x1->Set1x1Pos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height*3);
	this->_c_16x9->Set16x9Pos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height*4);
	this->_c_21x9->Set21x9Pos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height*5);

	// Setup Tick
	if (TheGame::Instance()->GetWindowManager()->GetFullScreen())
		this->_c_tick_fullscreen->SetTickPos(_dst_x + _offset_left, _dst_y + _offset_header);
	else
		this->_c_tick_fullscreen->SetTickPos(-1000, -1000);

	switch (TheGame::Instance()->GetWindowManager()->GetAspect())
	{
		case WinAspect::_4x3:
			this->_c_tick_ratio->SetTickPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height * 2);
			break;
		case WinAspect::_1x1:
			this->_c_tick_ratio->SetTickPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height * 3);
			break;
		case WinAspect::_16x9:
			this->_c_tick_ratio->SetTickPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height * 4);
			break;
		case WinAspect::_21x9:
			this->_c_tick_ratio->SetTickPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height * 5);
			break;
	}

	SetCursorPos();
}

void ConfigMenu::SetCursorPos()
{
	int _dst_x = getDstX();
	int _dst_y = getDstY();

	int _offset_header = 20 * Globals::sGuiScale;
	int _offset_left = 10 * Globals::sGuiScale;
	int _line_height = TheTextureManager::Instance()->getTextureSize(this->_c_fullscreen->getTextureId())[1] * Globals::sGuiScale;
	
	this->_c_cursor->SetChosenPos(_dst_x + _offset_left, _dst_y + _offset_header + _line_height * this->_c_cursor_pos);
}

void ConfigMenu::ExecuteCmd()
{
	switch (this->_c_cursor_pos)
	{
		case 0:
			TheGame::Instance()->GetWindowManager()->toggleFullScreen();
			SetConfigPos();
			break;
		case 2:
			TheGame::Instance()->GetWindowManager()->SetAspect(WinAspect::_4x3);
			SetConfigPos();
			break;
		case 3:
			TheGame::Instance()->GetWindowManager()->SetAspect(WinAspect::_1x1);
			SetConfigPos();
			break;
		case 4:
			TheGame::Instance()->GetWindowManager()->SetAspect(WinAspect::_16x9);
			SetConfigPos();
			break;
		case 5:
			TheGame::Instance()->GetWindowManager()->SetAspect(WinAspect::_21x9);
			SetConfigPos();
			break;
	}
}

void ConfigMenu::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
	this->_c_fullscreen->draw();
	this->_c_ratiotext->draw();
	this->_c_4x3->draw();
	this->_c_1x1->draw();
	this->_c_16x9->draw();
	this->_c_21x9->draw();

	this->_c_tick_fullscreen->draw();
	this->_c_tick_ratio->draw();

	this->_c_cursor->draw();
}


// FULLSCREEN ----------------------------------------------------------
ConfigFullScreen::ConfigFullScreen()
{
	// Setup Texture
	setTextureId("configmenu_fullscreen");
	TheTextureManager::Instance()->load("../Assets/textures/config_fullscreen.png", getTextureId(), TheGame::Instance()->getRenderer());

	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

ConfigFullScreen::~ConfigFullScreen()
{
}

void ConfigFullScreen::SetFullScreenPos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void ConfigFullScreen::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

// 4x3 ---------------------------------------------------------------------
Config_4x3::Config_4x3()
{
	// Setup Texture
	setTextureId("configmenu_4x3");
	TheTextureManager::Instance()->load("../Assets/textures/config_4x3.png", getTextureId(), TheGame::Instance()->getRenderer());

	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

Config_4x3::~Config_4x3()
{
}

void Config_4x3::Set4x3Pos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void Config_4x3::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

// 1x1 ----------------------------------------------------------------------
Config_1x1::Config_1x1()
{
	// Setup Texture
	setTextureId("configmenu_1x1");
	TheTextureManager::Instance()->load("../Assets/textures/config_1x1.png", getTextureId(), TheGame::Instance()->getRenderer());

	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

Config_1x1::~Config_1x1()
{
}

void Config_1x1::Set1x1Pos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void Config_1x1::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

// 16x9 -----------------------------------------------------------------------
Config_16x9::Config_16x9()
{
	// Setup Texture
	setTextureId("configmenu_16x9");
	TheTextureManager::Instance()->load("../Assets/textures/config_16x9.png", getTextureId(), TheGame::Instance()->getRenderer());


	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

Config_16x9::~Config_16x9()
{
}

void Config_16x9::Set16x9Pos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void Config_16x9::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}


// 21x9 --------------------------------------------------------------------------
Config_21x9::Config_21x9()
{
	// Setup Texture
	setTextureId("configmenu_21x9");
	TheTextureManager::Instance()->load("../Assets/textures/config_21x9.png", getTextureId(), TheGame::Instance()->getRenderer());


	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

Config_21x9::~Config_21x9()
{
}

void Config_21x9::Set21x9Pos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void Config_21x9::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}


// Tick -------------------------------------------------------------------------------
ConfigTick::ConfigTick()
{
	// Setup Texture
	setTextureId("configmenu_tick");
	TheTextureManager::Instance()->load("../Assets/textures/config_tick.png", getTextureId(), TheGame::Instance()->getRenderer());


	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

ConfigTick::~ConfigTick()
{
}

void ConfigTick::SetTickPos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void ConfigTick::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

// Chosen -----------------------------------------------------------------------------
ConfigChosen::ConfigChosen()
{
	// Setup Texture
	setTextureId("configmenu_chosen");
	TheTextureManager::Instance()->load("../Assets/textures/config_cursor.png", getTextureId(), TheGame::Instance()->getRenderer());


	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

ConfigChosen::~ConfigChosen()
{
}

void ConfigChosen::SetChosenPos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void ConfigChosen::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

// Ratio text
ConfigRatioText::ConfigRatioText()
{
	// Setup Texture
	setTextureId("configmenu_ratiotext");
	TheTextureManager::Instance()->load("../Assets/textures/config_ratio.png", getTextureId(), TheGame::Instance()->getRenderer());


	// Setup Position
	this->_grid = UIGrid::MID_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, -500 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

ConfigRatioText::~ConfigRatioText()
{
}

void ConfigRatioText::SetRatioTextPos(int dst_x, int dst_y)
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = dst_x;
	int _dst_y = dst_y;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void ConfigRatioText::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}
