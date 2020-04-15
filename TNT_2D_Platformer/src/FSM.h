#pragma once
#include <vector>
#include "ui/Title.h"
#include "ui/Config.h"

class GameState
{
protected:
	GameState();
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
};

class PauseState :public GameState {
public:
	PauseState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};

class RunningState :public GameState {
public:
	RunningState();
	void Enter();
	void Update();
	void Render();
	void Exit();
	void Resume();
};

class TitleState :public GameState {
private:
	TitleMenu* _t_menu;
	ConfigMenu* _t_config;
	bool _is_config;

public:
	TitleState();
	void Enter();
	void Update();
	void Render();
	void Exit();
};


class FSM {
private:
	std::vector<GameState*> states_;
public:
	FSM();
	~FSM();

	void Update();
	void Render();
	void ChangeState(GameState* state_ptr); //normal state change
	void PushState(GameState* state_ptr); //RunningState to PauseState
	void PopState(); //PauseState to RunningState
	void Clean();
	std::vector<GameState*>& GetStates();
};