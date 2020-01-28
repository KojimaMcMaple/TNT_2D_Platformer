#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

// Game Managers
#include "TextureManager.h"
#include "CollisionManager.h"

// Game Objects
#include "Level.h"
#include "Player.h"

class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	// simply set the running variable to true
	void init() { m_bRunning = true; }

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// public functions
	bool isKeyDown(SDL_Scancode keyboard_code);
	void handleEvents();
	void update();
	void render();
	void clean();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	// getters
	SDL_Renderer* getRenderer();
	int GetOffsetPositionX();
	int GetOffsetPositionY();

	// setters
	void SetOffsetPositionX(int x_distance);
	void SetOffsetPositionY(int y_distance);

	// REDUNDANT
	glm::vec2 getMousePosition();
	glm::vec2 getTargetPosition();

private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	static Game* s_pInstance;
	int m_currentFrame;
	bool m_bRunning;
	const Uint8* key_states_ = nullptr;

	// GameObjects
	Level* level_ptr_;
	Player* player_ptr_;
	void createGameObjects();

	// Movement offset
	int offset_position_x_;
	int offset_position_y_;

	// REDUNDANT
	glm::vec2 m_mousePosition;
};

typedef Game TheGame;

#endif /* defined (__Game__) */

