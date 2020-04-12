#include "WindowManager.h"

#include "..\Game.h"
#include "..\Globals.h"

WindowManager::WindowManager(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int _flag = 0;
	if (fullscreen) _flag = SDL_WINDOW_FULLSCREEN;
	
	this->base_w = Globals::sWindowWidth;
	this->base_h = Globals::sWindowHeight;
	this->_aspect = WinAspect::_4x3;
	this->_fullScreen = fullscreen;
	this->_mainWindow = SDL_CreateWindow(title, x, y, width, height, _flag);
}

WindowManager::~WindowManager() {}



void WindowManager::resizeMainWindow(int width, int height)
{
	// TODO (@nghialam): Resize to bigger aspect ratio cause the game to render green at border?
	TheGame::Instance()->GetCamera()->SetWorldRect(0, 0, width, height);
	TheGame::Instance()->GetLevel()->UpdateVisibleTileList();
	SDL_SetWindowSize(this->_mainWindow, width, height);

}

void WindowManager::toggleFullScreen()
{
	int _flag = 0;
	if (!this->_fullScreen) _flag = SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(this->_mainWindow, _flag);
	this->_fullScreen = !this->_fullScreen;
}

void WindowManager::SetAspect(WinAspect aspect)
{
	this->_aspect = aspect;
	switch (this->_aspect)
	{
		case WinAspect::_16x9:
			Globals::sWindowHeight = this->base_h;
			Globals::sWindowWidth = this->base_h * (16.0f / 9);
			break;
		case WinAspect::_21x9:
			Globals::sWindowHeight = this->base_h;
			Globals::sWindowWidth = this->base_h * (21.0f / 9);
			break;
		case WinAspect::_4x3:
			Globals::sWindowHeight = this->base_h;
			Globals::sWindowWidth = this->base_h * (4.0f / 3);
			break;
		case WinAspect::_1x1:
			Globals::sWindowHeight = this->base_h;
			Globals::sWindowWidth = this->base_h;
			break;
	}

	resizeMainWindow(Globals::sWindowWidth, Globals::sWindowHeight);
}

SDL_Window* WindowManager::GetMainWindow()
{
	return this->_mainWindow;
}

bool WindowManager::GetFullScreen()
{
	return this->_fullScreen;
}
