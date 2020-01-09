#include <iostream>
#include "Engine.h"

#define WIDTH 1024
#define HEIGHT 768
#define FPS 60

Engine::Engine():is_engine_running(false) {}

Engine::~Engine(){}

bool Engine::Init(const char* in_win_title, int in_win_xpos, int in_win_ypos, int in_win_width, int in_win_height, int in_win_flags) {
	std::cout << "Initializing game." << std::endl;
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		// Create the window.
		main_window = SDL_CreateWindow(in_win_title, in_win_xpos, in_win_ypos, in_win_width, in_win_height, in_win_flags);
		if (main_window != nullptr) { // Window init success. 
			renderer = SDL_CreateRenderer(main_window, -1, 0);
			if (renderer != nullptr) { // Renderer init success.

			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	keystates = SDL_GetKeyboardState(nullptr);

	is_engine_running = true; // Everything is okay, start the engine.
	std::cout << "Success!" << std::endl;
	return true;
}


void Engine::Wake() {
	start_time = SDL_GetTicks();
}

void Engine::Sleep() {
	end_time = SDL_GetTicks();
	delta_time = end_time - start_time;
	if (delta_time < fps) { // Engine has to sleep.
		SDL_Delay(fps - delta_time);
	}
}

void Engine::HandleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: // User pressed window's 'x' button.
			is_engine_running = false;
			break;
		case SDL_KEYDOWN: // Try SDL_KEYUP instead.
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				is_engine_running = false;
			}
			break;
		}
	}
}

// Keyboard utility function.
bool Engine::IsKeyDown(SDL_Scancode in_code) {
	if (keystates != nullptr) {
		if (keystates[in_code] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Engine::Update() {

}

void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer); // Clear the screen with the draw color.
	// Render stuff.

	// Draw anew.
	SDL_RenderPresent(renderer);
}

void Engine::Clean() {
	std::cout << "Cleaning game." << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
}

int Engine::Run() {
	if (Engine::Init("Main_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false) {
		return 1;
	}
	while (is_engine_running) {
		Wake();
		HandleEvents();
		Update();
		Render();
		if (is_engine_running) {
			Sleep();
		}
	}
	Clean();

	return 0;
}