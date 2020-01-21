#pragma once
#ifndef __State__
#define __State__

class State
{
private:
	State(); //prevents instantiation outside class
	~State();
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Resume();
	virtual void Exit() = 0;
};

#endif