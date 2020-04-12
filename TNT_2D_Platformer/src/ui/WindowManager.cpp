#include "WindowManager.h"

WindowManager::WindowManager(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int _flag = 0;
	if (fullscreen) _flag = SDL_WINDOW_FULLSCREEN;
	
	this->_fullScreen = fullscreen;
	this->_mainWindow = SDL_CreateWindow(title, x, y, width, height, _flag);
}

WindowManager::~WindowManager() {}



void WindowManager::resizeMainWindow(int width, int height)
{
	SDL_SetWindowSize(this->_mainWindow, width, height);
}

void WindowManager::toggleFullScreen()
{
	int _flag = 0;
	if (!this->_fullScreen) _flag = SDL_WINDOW_FULLSCREEN;

	SDL_SetWindowFullscreen(this->_mainWindow, _flag);
	this->_fullScreen = !this->_fullScreen;
}

SDL_Window* WindowManager::GetMainWindow()
{
	return this->_mainWindow;
}

bool WindowManager::GetFullScreen()
{
	return this->_fullScreen;
}
