#pragma once
#ifndef __GameObject__
#define __GameObject__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

enum GameObjectType {
	PLAYER,
	ENEMY,
	NUM_OF_TYPES
};

class GameObject {
private:
	SDL_Rect src, dst;
	SDL_Texture* texture = nullptr;
	int speed;
	bool is_active = true;
	bool is_collided = false;
public:
	GameObject();
	~GameObject();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

	// SRC ACCESSOR MUTATOR
	SDL_Rect* GetSrcPosition();
	int GetSrcPositionX();
	int GetSrcPositionY();
	void SetSrcPosition(int in_x, int in_y);

	// DST ACCESSOR MUTATOR
	SDL_Rect* GetDstPosition();
	int GetDstPositionX();
	int GetDstPositionY();
	void SetDstPosition(int in_x, int in_y);

	// TEXTURE ACCESSOR MUTATOR
	SDL_Texture* GetTexturePointer();

	int GetSpeed();
	void SetSpeed(int in_speed);
};

#endif