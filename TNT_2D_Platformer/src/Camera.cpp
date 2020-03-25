#include "Camera.h"

Camera::Camera()
{
	SetWorldRect(0, 0, Globals::sWindowWidth, Globals::sWindowHeight);
}

Camera::~Camera()
{
}

void Camera::update()
{
}

void Camera::draw()
{
}

void Camera::clean()
{
}

void Camera::RefocusCamera(Player* player_ptr, Level* level_ptr)
{
	if (player_ptr->GetWorldRect()->x > Globals::sWindowWidth/2 && player_ptr->GetWorldRect()->x < level_ptr->GetLevelMaxPosX()- Globals::sWindowWidth / 2) {
		SetWorldRectX(player_ptr->GetWorldRectCenterX() - GetWorldRect()->w / 2);
	}
	if (player_ptr->GetWorldRect()->y > Globals::sWindowHeight / 2 && player_ptr->GetWorldRect()->y < level_ptr->GetLevelMaxPosY() - Globals::sWindowHeight / 2) {
		SetWorldRectY(player_ptr->GetWorldRectCenterY() - GetWorldRect()->h / 2);
	}
}
