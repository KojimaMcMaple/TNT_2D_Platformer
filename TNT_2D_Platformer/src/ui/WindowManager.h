#pragma once

#include <SDL.h>

enum class WinAspect
{
	_16x9,
	_21x9,
	_4x3,
	_1x1
};

class WindowManager
{
private:
	bool _fullScreen;
	SDL_Window* _mainWindow;
	WinAspect _aspect;
	int base_w;
	int base_h;

public:
	WindowManager(const char* title, int x, int y, int width, int height, bool fullscreen);
	~WindowManager();
	void resizeMainWindow(int width, int height);
	void toggleFullScreen();

	// Setter
	void SetAspect(WinAspect aspect);

	// Getter
	SDL_Window* GetMainWindow();
	bool GetFullScreen();
};

