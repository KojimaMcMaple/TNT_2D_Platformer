#include "Title.h"
#include "..\Game.h"

TitleText::TitleText()
{
	// Setup Texture
	setTextureId("title_text");
	TheTextureManager::Instance()->load("../Assets/textures/title.png", getTextureId(), TheGame::Instance()->getRenderer());
	
	setTextPos();

	// Setup Position
	this->_grid = UIGrid::BOT_CENTER;
	this->_state = UIState::ACTIVE;
	this->_length = 10;
	this->_timer = 10;
	this->_active_position = { 0, 0 };
	this->_inactive_offset = { 0, 200 };
	this->_active_type = TweenType::OUT_BACK;
	this->_deactive_type = TweenType::IN_BACK;
}

TitleText::~TitleText()
{
}

void TitleText::setTextPos()
{
	int _src_x = 0;
	int _src_y = 0;
	int _src_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0];
	int _src_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1];
	setSrc(_src_x, _src_y, _src_w, _src_h);

	int _dst_x = Globals::sWindowWidth / 2 - (TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale) / 2;
	int _dst_y = Globals::sWindowHeight / 2 + Globals::sWindowHeight / 2 / 3;
	int _dst_w = TheTextureManager::Instance()->getTextureSize(getTextureId())[0] * Globals::sGuiScale;
	int _dst_h = TheTextureManager::Instance()->getTextureSize(getTextureId())[1] * Globals::sGuiScale;
	setDst(_dst_x, _dst_y, _dst_w, _dst_h);
}

void TitleText::change_text(TitleMenuState cur_state)
{
	switch (cur_state)
	{
		case TitleMenuState::TITLE:
		{
			setTextureId("title_text");
			TheTextureManager::Instance()->load("../Assets/textures/title.png", getTextureId(), TheGame::Instance()->getRenderer());
			setTextPos();
			break;
		}
		case TitleMenuState::NEWGAME:
		{
			setTextureId("title_newgame");
			TheTextureManager::Instance()->load("../Assets/textures/title_newgame.png", getTextureId(), TheGame::Instance()->getRenderer());
			setTextPos();
			break;
		}
		case TitleMenuState::CONFIG:
		{
			setTextureId("title_option");
			TheTextureManager::Instance()->load("../Assets/textures/title_option.png", getTextureId(), TheGame::Instance()->getRenderer());
			setTextPos();
			break;
		}
		case TitleMenuState::QUIT:
		{
			setTextureId("title_quit");
			TheTextureManager::Instance()->load("../Assets/textures/title_quit.png", getTextureId(), TheGame::Instance()->getRenderer());
			setTextPos();
			break;
		}
	}
}

void TitleText::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}


TitleMenu::TitleMenu()
{
	this->_t_text = new TitleText();
	this->_cur_state = TitleMenuState::TITLE;
}

TitleMenu::~TitleMenu()
{
}

void TitleMenu::draw()
{
	this->_t_text->draw();
}

TitleText* TitleMenu::GetText()
{
	return this->_t_text;
}

TitleMenuState TitleMenu::GetMenuState()
{
	return this->_cur_state;
}

void TitleMenu::SetMenuState(TitleMenuState cur_state)
{
	this->_cur_state = cur_state;
	this->_t_text->change_text(cur_state);
}
