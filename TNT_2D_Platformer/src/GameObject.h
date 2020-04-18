#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <glm\vec2.hpp>
#include <string>
#include <vector>
#include <SDL.h>

#include "Globals.h"
#include "Util.h"
#include "GameObjectType.h"
#include "AnimState.h"
#include "AnimSprite.h"

class GameObject {
private:
	// GAME ATTR
	int hp_;
	int atk_power_;

	// POSITIONING
	SDL_Rect world_rect_; //"real" rect
	
	// RENDERING
	SDL_Rect src_, dst_;
	std::string texture_id_ = "";
	bool animationEnded = false;

	// SOUND
	std::vector<std::string> sfx_id_list_;

	// PHYSICS
	float velocity_x_ = 0.0f;
	float velocity_y_= 0.0f;
	float max_velocity_x_ = 0.0f;
	float max_velocity_y_= 0.0f;
	float acceleration_x_= 0.0f;
	float acceleration_y_= 0.0f;
	float max_acceleration_x_= 0.0f;
	float max_acceleration_y_= 0.0f;
	float drag_= 0.0f;
	float gravity_= 0.0f;
	int move_direction_ = 1;

	// COLLISION
	SDL_Rect hit_box_;
	int hit_box_manual_offset_x_ = 0;
	int hit_box_manual_offset_y_ = 0;
	bool is_hit_box_visible_ = true;
	bool is_grounded_ = false;
	bool is_collidable_;

	SDL_Rect atk_hit_box_;
	bool is_atk_hit_box_active_ = false;
	int i_frames_ = 0;

	SDL_Rect sight_rect_;

	GameObjectType m_type; //redundant ?

	// TRANSFORM
	int custom_pivot_x_;
	int custom_pivot_y_;

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
	int curr_frame_;
	int curr_row_;
	int curr_col_;
	int checking_anim_state_ = -1; //checking var to reset curr_frame_
	AnimState anim_state_;
	std::vector<AnimSprite*> anim_list_;

public:
	GameObject();
	~GameObject();

	// Update the object
	virtual void update() = 0;

	// Draw the object
	virtual void draw() = 0;
	void Animate();

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	int GetHP();
	int GetAtkPower();
	SDL_Rect* GetWorldRect();
	int GetWorldRectRightmostX();
	int GetWorldRectLowermostY();
	int GetWorldRectCenterX();
	int GetWorldRectCenterY();
	SDL_Rect* getSrc();
	SDL_Rect* getDst();
	int getDstX();
	int getDstRightmostX();
	int getDstY();
	int getDstLowermostY();
	int getDstW();
	int getDstH();
	int getDstCenterX();
	int getDstCenterY();
	SDL_Rect* getHitBox();
	int getHitBoxX();
	int getHitBoxRightmostX();
	int getHitBoxY();
	int getHitBoxLowermostY();
	int getHitBoxW();
	int getHitBoxH();
	int getHitBoxCenterX();
	int getHitBoxCenterY();
	int getHitBoxOffsetX();
	int getHitBoxOffsetY();
	bool IsHitBoxVisible();
	SDL_Rect* GetAtkHitBox();
	bool IsAtkHitBoxActive();
	int GetIFrames();
	SDL_Rect* GetSightRect();
	bool IsGrounded();
	bool IsCollidable();
	std::string getTextureId();
	int getCustomPivotX();
	int getCustomPivotY();
	float getVelocityX();
	float getVelocityY();
	float getMaxVelocityX();
	float getMaxVelocityY();
	float getAccelerationX();
	float getAccelerationY();
	float getMaxAccelerationX();
	float getMaxAccelerationY();
	float getDrag();
	float getGravity();
	int getMoveDirection();
	int getCurrFrame();
	int getCurrRow();
	int getCurrCol();
	bool HasEndedAnimation();
	AnimState getAnimState();
	std::vector<AnimSprite*>& GetAnimList();
	GameObjectType getType();
	glm::vec2 getPosition();
	glm::vec2 getRotation();
	glm::vec2 getScale();
	glm::vec2 getVelocityVect();
	glm::vec2 getAcceleration();
	int getWidth();
	int getHeight();

	// setters for common variables
	void SetHP(int value);
	void SetAtkPower(int value);
	void SetWorldRect(int x, int y, int w, int h);
	void SetWorldRectX(int coord);
	void SetWorldRectY(int coord);
	void setSrc(SDL_Rect src_ptr);
	void setSrc(int x, int y, int w, int h);
	void setSrcX(int coord);
	void setSrcY(int coord);
	void setDst(SDL_Rect dst_ptr);
	void setDst(int x, int y, int w, int h);
	void setDstX(int coord);
	void setDstY(int coord);
	void SetWorldXAndHitBox(int coord);
	void SetWorldYAndHitBox(int coord);
	void SetHitBoxXAndWorld(int coord);
	void SetHitBoxYAndWorld(int coord);
	void setHitBox(int x, int y, int w, int h);
	void setHitBoxX(int coord);
	void setHitBoxY(int coord);
	void setHitBoxOffsetX(int coord);
	void setHitBoxOffsetY(int coord);
	void SetHitBoxVisibility(bool toggle);
	void SetAtkHitBox(int x, int y, int w, int h);
	void SetAtkHitBoxX(int value);
	void SetAtkHitBoxY(int value);
	void SetAtkHitBoxActive(bool toggle);
	void SetIFrames(int value);
	void SetSightRect(int x, int y, int w, int h);
	void SetSightRectX(int value);
	void SetSightRectY(int value);
	void SetGrounded(bool toggle);
	void SetCollidable(bool toggle);
	void setTextureId(std::string id); //cleanup is done by manager
	void addSfxId(std::string id); //cleanup is done by manager
	void setCustomPivotX(int coord);
	void setCustomPivotY(int coord);
	void setVelocityX(float value);
	void setVelocityY(float value);
	void setMaxVelocityX(float value);
	void setMaxVelocityY(float value);
	void setAccelerationX(float value);
	void setAccelerationY(float value);
	void setMaxAccelerationX(float value);
	void setMaxAccelerationY(float value);
	void setDrag(float value);
	void setGravity(float value);
	void setMoveDirection(int value);
	void setType(GameObjectType newType);
	void setCurrFrame(int value);
	void setCurrRow(int value);
	void setCurrCol(int value);
	void setAnimState(AnimState newState);
	void InitAnimList();
	void setAcceleration(glm::vec2 newAcceleration);
	void setPosition(glm::vec2 newPosition);
	void setWidth(int newWidth);
	void setHeight(int newHeight);
	void setVelocityVect(glm::vec2 newVelocity);
};

#endif