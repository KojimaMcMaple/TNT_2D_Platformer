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

SDL_Rect* GameObject::getCollideBox()
{
	return &collide_box_;
}

std::string GameObject::getTextureId()
{
	return texture_id_;
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

glm::vec2 GameObject::getVelocity()
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

void GameObject::setSrc(int x, int y, int w, int h)
{
	src_ = { x,y,w,h };
}

void GameObject::setDst(int x, int y, int w, int h)
{
	dst_ = { x,y,w,h };
}

void GameObject::setCollideBox(int x, int y, int w, int h)
{
	collide_box_ = { x,y,w,h };
}

void GameObject::setTextureId(std::string id)
{
	texture_id_ = id;
}

void GameObject::addSfxId(std::string id)
{
	sfx_id_list_.push_back(id);
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

void GameObject::setVelocity(glm::vec2 newVelocity)
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
