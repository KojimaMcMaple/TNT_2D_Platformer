#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Engine {
private:
	// Global engine variables.
	bool is_engine_running = false; // Loop control flag.
	int speed = 5; // Speed of box.
	const Uint8* keystates; // Keyboard state container.
	Uint32 start_time, end_time, delta_time, fps; // Fixed timestep variables.
	SDL_Window* main_window; // This represents the SDL window.
	SDL_Renderer* renderer; // This represents the buffer to draw to.

public:
	Engine();
	~Engine();

	void CreateGameObjects();

	bool Init(const char* window_title, int window_xpos, int window_ypos, int window_width, int window_height, int window_flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	int Run();
	bool IsKeyDown(SDL_Scancode scancode);

	static Engine& Instance();
};

