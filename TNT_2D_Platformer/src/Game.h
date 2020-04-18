#pragma once
#ifndef __Game__
#define __Game__

// Core Libraries
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

// Game Managers
#include "ui/WindowManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Controller.h"
#include "FSM.h"
#include "SoundId.h"

// Game Objects
#include "ui/UI.h"
#include "Level.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"
#include "Arrow.h"
#include "ScoreBoard.h"

class Game
{
private:
	Game();
	~Game();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	WindowManager* m_wm;
	Controller* m_controller;
	FSM* fsm_;

	static Game* s_pInstance;
	Uint32 m_frames;
	bool m_bRunning;
	const Uint8* key_states_ = nullptr;

	// GameObjects
	UI* title_screen_ptr_;
	UI* pause_screen_ptr_;
	Level* level_ptr_;
	Camera* camera_ptr_;
	Player* player_ptr_;
	std::vector<Arrow*> m_pArrowVec;
	std::vector<Enemy*> enemy_list_;
	std::vector<Enemy*> dead_enemy_list_;

	// UI
	TextElement* m_scoreBoard;

	// Movement offset
	bool is_jump_key_pressable_ = true;

	// REDUNDANT
	glm::vec2 m_mousePosition;

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
	void init() {}

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	// public functions
	bool isKeyDown(SDL_Scancode keyboard_code);
	void handleEvents();
	void update();
	void render();
	void clean();

	// a function to access the private running variable
	bool running() { return m_bRunning; }
	void setRunning(bool toggle) { this->m_bRunning = toggle; }

	void createGameObjects();
	void CheckCollision();
	void UpdateGameObjects();
	void RenderGameObjects();

	// getters
	Uint32 getFrames() const;
	SDL_Renderer* getRenderer();
	FSM& GetFSM();
	WindowManager* GetWindowManager();
	Controller* GetController();
	UI& GetTitleScreen();
	UI& GetPauseScreen();
	Camera* GetCamera();
	Level* GetLevel();

	// setters
	void setFrames(Uint32 frames);

	// REDUNDANT
	glm::vec2 getMousePosition();
	glm::vec2 getTargetPosition();
};

typedef Game TheGame;

#endif /* defined (__Game__) */

