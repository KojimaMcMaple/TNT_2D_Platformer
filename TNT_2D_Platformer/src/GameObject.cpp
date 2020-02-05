#include "GameObject.h"

GameObject::GameObject()
{
	m_position = glm::vec2(0, 0);
	m_rotation = glm::vec2(0, 0);
	m_scale = glm::vec2(1.0f, 1.0f);
	m_velocity = glm::vec2(0, 0);
	m_acceleration = glm::vec2(0, 0);
}

GameObject::~GameObject()
{
}


SDL_Rect* GameObject::getSrc()
{
	return &src_;
}

SDL_Rect* GameObject::getDst()
{
	return &dst_;
}

int GameObject::getDstX()
{
	return dst_.x;
}

int GameObject::getDstRightmostX()
{
	return dst_.x + dst_.w;
}

int GameObject::getDstY()
{
	return dst_.y;
}

int GameObject::getDstLowermostY()
{
	return dst_.y + dst_.h;
}

int GameObject::getDstW()
{
	return dst_.w;
}

int GameObject::getDstH()
{
	return dst_.h;
}

int GameObject::getDstCenterX()
{
	return dst_.x + dst_.w / 2;
}

int GameObject::getDstCenterY()
{
	return dst_.y + dst_.h / 2;
}

SDL_Rect* GameObject::getHitBox()
{
	return &hit_box_;
}

int GameObject::getHitBoxX()
{
	return hit_box_.x;
}

int GameObject::getHitBoxRightmostX()
{
	return hit_box_.x + hit_box_.w;
}

int GameObject::getHitBoxY()
{
	return hit_box_.y;
}

int GameObject::getHitBoxLowermostY()
{
	return hit_box_.y + hit_box_.h;
}

int GameObject::getHitBoxW()
{
	return hit_box_.w;
}

int GameObject::getHitBoxH()
{
	return hit_box_.h;
}

int GameObject::getHitBoxCenterX()
{
	return hit_box_.x + hit_box_.w / 2;
}

int GameObject::getHitBoxCenterY()
{
	return hit_box_.y + hit_box_.h / 2;
}

int GameObject::getHitBoxOffsetX()
{
	return hit_box_manual_offset_x_;
}

int GameObject::getHitBoxOffsetY()
{
	return hit_box_manual_offset_y_;
}

bool GameObject::isHitBoxVisible()
{
	return is_hit_box_visible_;
}

std::string GameObject::getTextureId()
{
	return texture_id_;
}

int GameObject::getCustomPivotX()
{
	return custom_pivot_x_;
}

int GameObject::getCustomPivotY()
{
	return custom_pivot_y_;
}

float GameObject::getVelocityX()
{
	return velocity_x_;
}

float GameObject::getVelocityY()
{
	return velocity_y_;
}

float GameObject::getMaxVelocityX()
{
	return max_velocity_x_;
}

float GameObject::getMaxVelocityY()
{
	return max_velocity_y_;
}

float GameObject::getAccelerationX()
{
	return acceleration_x_;
}

float GameObject::getAccelerationY()
{
	return acceleration_y_;
}

float GameObject::getMaxAccelerationX()
{
	return max_acceleration_x_;
}

float GameObject::getMaxAccelerationY()
{
	return max_acceleration_y_;
}

float GameObject::getDrag()
{
	return drag_;
}

float GameObject::getGravity()
{
	return gravity_;
}

int GameObject::getMoveDirection()
{
	return move_direction_;
}

glm::vec2 GameObject::getPosition()
{
	return m_position;
}

glm::vec2 GameObject::getRotation()
{
	return m_rotation;
}

glm::vec2 GameObject::getScale()
{
	return m_scale;
}

glm::vec2 GameObject::getVelocityVect()
{
	return m_velocity;
}

glm::vec2 GameObject::getAcceleration()
{
	return m_acceleration;
}

int GameObject::getWidth()
{
	return m_width;
}

int GameObject::getHeight()
{
	return m_height;
}

bool GameObject::getIsColliding()
{
	return m_isColliding;
}

GameObjectType GameObject::getType()
{
	return m_type;
}

SteeringState GameObject::getSteeringState()
{
	return m_state;
}

void GameObject::setSrc(SDL_Rect src_rect)
{
	src_ = { src_rect.x,src_rect.y,src_rect.w,src_rect.h };
}

void GameObject::setSrc(int x, int y, int w, int h)
{
	src_ = { x,y,w,h };
}

void GameObject::setDst(int x, int y, int w, int h)
{
	dst_ = { x,y,w,h };
}

void GameObject::setDstX(int x)
{
	dst_.x = x;
}

void GameObject::setDstY(int y)
{
	dst_.y = y;
}

void GameObject::setDstXAndHitBox(int x)
{
	dst_.x = x;
	setHitBoxX(getDstCenterX() - getHitBoxW() / 2 + getHitBoxOffsetX());
}

void GameObject::setDstYAndHitBox(int y)
{
	dst_.y = y;
	setHitBoxY(getDstCenterY() - getHitBoxH() / 2 + getHitBoxOffsetY());
}

void GameObject::setHitBox(int x, int y, int w, int h)
{
	hit_box_ = { x,y,w,h };
}

void GameObject::setHitBoxX(int coord)
{
	hit_box_.x = coord;
}

void GameObject::setHitBoxY(int coord)
{
	hit_box_.y = coord;
}

void GameObject::setHitBoxOffsetX(int coord)
{
	hit_box_manual_offset_x_ = coord;
}

void GameObject::setHitBoxOffsetY(int coord)
{
	hit_box_manual_offset_y_ = coord;
}

void GameObject::setHitBoxVisibility(bool toggle)
{
	is_hit_box_visible_ = toggle;
}

void GameObject::setGrounded(bool toggle)
{
	is_on_ground_ = toggle;
}

void GameObject::setTextureId(std::string id)
{
	texture_id_ = id;
}

void GameObject::addSfxId(std::string id)
{
	sfx_id_list_.push_back(id);
}

void GameObject::setCustomPivotX(int coord)
{
	custom_pivot_x_ = coord;
}

void GameObject::setCustomPivotY(int coord)
{
	custom_pivot_y_ = coord;
}

void GameObject::setVelocityX(float value)
{
	velocity_x_ = value;
}

void GameObject::setVelocityY(float value)
{
	velocity_y_ = value;
}

void GameObject::setMaxVelocityX(float value)
{
	max_velocity_x_ = value;
}

void GameObject::setMaxVelocityY(float value)
{
	max_velocity_y_ = value;
}

void GameObject::setAccelerationX(float value)
{
	acceleration_x_ = value;
}

void GameObject::setAccelerationY(float value)
{
	acceleration_y_ = value;
}

void GameObject::setMaxAccelerationX(float value)
{
	max_acceleration_x_ = value;
}

void GameObject::setMaxAccelerationY(float value)
{
	max_acceleration_y_ = value;
}

void GameObject::setDrag(float value)
{
	drag_ = value;
}

void GameObject::setGravity(float value)
{
	gravity_ = value;
}

void GameObject::setMoveDirection(int value)
{
	move_direction_ = value;
}

void GameObject::setPosition(glm::vec2 newPosition)
{
	m_position = newPosition;
}

void GameObject::setWidth(int newWidth)
{
	m_width = newWidth;
}

void GameObject::setHeight(int newHeight)
{
	m_height = newHeight;
}

void GameObject::setVelocityVect(glm::vec2 newVelocity)
{
	m_velocity = newVelocity;
}

void GameObject::setIsColliding(bool collision)
{
	m_isColliding = collision;
}

void GameObject::setType(GameObjectType newType)
{
	m_type = newType;
}

void GameObject::setSteeringState(SteeringState newState)
{
	m_state = newState;
}

void GameObject::setAcceleration(glm::vec2 newAcceleration)
{
	m_acceleration = newAcceleration;
}
