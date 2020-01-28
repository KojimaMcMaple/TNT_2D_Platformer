#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <glm\vec2.hpp>
#include <string>
#include <vector>
#include <SDL.h>

#include "GameObjectType.h"
#include "SteeringState.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	// Update the object
	virtual void update() = 0;

	// Draw the object
	virtual void draw() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	SDL_Rect* getSrc();
	SDL_Rect* getDst();
	int getDstX();
	int getDstY();
	int getDstW();
	int getDstH();
	SDL_Rect* getCollideBox();
	bool isCollideBoxVisible();
	bool getIsColliding();
	std::string getTextureId();
	int getVelocityX();
	int getVelocityY();
	GameObjectType getType();
	SteeringState getSteeringState();
	glm::vec2 getPosition();
	glm::vec2 getRotation();
	glm::vec2 getScale();
	glm::vec2 getVelocityVect();
	glm::vec2 getAcceleration();
	int getWidth();
	int getHeight();

	// setters for common variables
	void setSrc(SDL_Rect src_ptr);
	void setSrc(int x, int y, int w, int h);
	void setDst(int x, int y, int w, int h);
	void setDstX(int x);
	void setDstY(int y);
	void setCollideBox(int x, int y, int w, int h);
	void setCollideBoxVisibility(bool toggle);
	void setIsColliding(bool collision);
	void setTextureId(std::string id); //cleanup is done by manager
	void addSfxId(std::string id); //cleanup is done by manager
	void setVelocityX(int velocity);
	void setVelocityY(int velocity);
	void setType(GameObjectType newType);
	void setSteeringState(SteeringState newState);
	void setAcceleration(glm::vec2 newAcceleration);
	void setPosition(glm::vec2 newPosition);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocityVect(glm::vec2 newVelocity);

private:
	// RENDERING
	SDL_Rect src_, dst_;
	std::string texture_id_;

	// SOUND
	std::vector<std::string> sfx_id_list_;
	
	// PHYSICS
	int velocity_x_;
	int velocity_y_;

	// collision variables
	SDL_Rect collide_box_;
	bool is_collide_visible = false;
	bool m_isColliding;
	GameObjectType m_type;
	SteeringState m_state;

	// LEGACY
	// transform variables
	glm::vec2 m_position;
	glm::vec2 m_rotation;
	glm::vec2 m_scale;

	// movement variables
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	// size variables
	int m_width;
	int m_height;

	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
};

#endif