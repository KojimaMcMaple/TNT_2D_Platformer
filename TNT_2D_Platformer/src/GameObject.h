#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <glm\vec2.hpp>
#include <string>
#include <SDL.h>

#include "GameObjectType.h"
#include "SteeringState.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	SDL_Rect* getSrc();
	SDL_Rect* getDst();
	SDL_Rect* getCollideBox();
	std::string getTextureId();
	glm::vec2 getPosition();
	glm::vec2 getRotation();
	glm::vec2 getScale();
	glm::vec2 getVelocity();
	glm::vec2 getAcceleration();
	int getWidth();
	int getHeight();
	bool getIsColliding();
	GameObjectType getType();
	SteeringState getSteeringState();

	// setters for common variables
	void setSrc(int x, int y, int w, int h);
	void setDst(int x, int y, int w, int h);
	void setCollideBox(int x, int y, int w, int h);
	void setTextureId(std::string id);
	void setPosition(glm::vec2 newPosition);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocity(glm::vec2 newVelocity);
	void setIsColliding(bool collision);
	void setType(GameObjectType newType);
	void setSteeringState(SteeringState newState);
	void setAcceleration(glm::vec2 newAcceleration);

private:
	// rendering variables
	SDL_Rect src_, dst_;
	
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
	std::string texture_id_;

	// collision variables
	SDL_Rect collide_box_;
	bool is_collide_visible = false;
	bool m_isColliding;
	GameObjectType m_type;
	SteeringState m_state;
};

#endif