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

SDL_Rect* GameObject::getCollideBox()
{
	return &collide_box_;
}

int GameObject::getCollideBoxX()
{
	return collide_box_.x;
}

int GameObject::getCollideBoxRightmostX()
{
	return collide_box_.x + collide_box_.w;
}

int GameObject::getCollideBoxY()
{
	return collide_box_.y;
}

int GameObject::getCollideBoxLowermostY()
{
	return collide_box_.y + collide_box_.h;
}

int GameObject::getCollideBoxW()
{
	return collide_box_.w;
}

int GameObject::getCollideBoxH()
{
	return collide_box_.h;
}

int GameObject::getCollideBoxCenterX()
{
	return collide_box_.x + collide_box_.w / 2;
}

int GameObject::getCollideBoxCenterY()
{
	return collide_box_.y + collide_box_.h / 2;
}

bool GameObject::isCollideBoxVisible()
{
	return is_collide_box_visible;
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

int GameObject::getVelocityX()
{
	return velocity_x_;
}

int GameObject::getVelocityY()
{
	return velocity_y_;
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

void GameObject::setCollideBox(int x, int y, int w, int h)
{
	collide_box_ = { x,y,w,h };
}

void GameObject::setCollideBoxX(int coord)
{
	collide_box_.x = coord;
}

void GameObject::setCollideBoxY(int coord)
{
	collide_box_.y = coord;
}

void GameObject::setCollideBoxVisibility(bool toggle)
{
	is_collide_box_visible = toggle;
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

void GameObject::setVelocityX(int velocity)
{
	velocity_x_ = velocity;
}

void GameObject::setVelocityY(int velocity)
{
	velocity_y_ = velocity;
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
