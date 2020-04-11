#include "Camera.h"
#include "Game.h"

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

void Camera::draw(GameObject* obj_ptr)
{
	int cam_x = GetWorldRect()->x;
	int cam_y = GetWorldRect()->y;
	int cam_max_x = GetWorldRectRightmostX();
	int cam_max_y = GetWorldRectLowermostY();
	
	int world_x = obj_ptr->GetWorldRect()->x;
	int world_y = obj_ptr->GetWorldRect()->y;
	int world_max_x = obj_ptr->GetWorldRectRightmostX();
	int world_max_y = obj_ptr->GetWorldRectLowermostY();

	int dst_x = world_x - cam_x;
	int dst_y = world_y - cam_y;
	if (world_max_y >= cam_y && world_y <= cam_max_y) {
		if (world_max_x >= cam_x && world_x <= cam_max_x) {
			obj_ptr->setDstX(dst_x);
			obj_ptr->setDstY(dst_y);
			obj_ptr->draw();
		}
	}

	// HITBOX RENDERING
	if (obj_ptr->IsHitBoxVisible()) {
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 150, 0, 50);

		SDL_Rect temp_rect = { obj_ptr->getHitBoxX() - cam_x,obj_ptr->getHitBoxY() - cam_y, obj_ptr->getHitBoxW(), obj_ptr->getHitBoxH() };
		SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &temp_rect);

		if (obj_ptr->IsAtkHitBoxActive()) {
			SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 150, 0, 0, 50);

			SDL_Rect atk_temp_rect = { obj_ptr->GetAtkHitBox()->x - cam_x,obj_ptr->GetAtkHitBox()->y - cam_y, obj_ptr->GetAtkHitBox()->w, obj_ptr->GetAtkHitBox()->h };
			SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &atk_temp_rect);
		}
	}
}

void Camera::clean()
{
}

void Camera::RefocusCamera(Player* player_ptr, Level* level_ptr)
{
	//std::cout << GetWorldRect()->x << std::endl;
	if (player_ptr->GetWorldRectCenterX() > Globals::sWindowWidth/2 && player_ptr->GetWorldRectCenterX() < level_ptr->GetLevelMaxPosX()- Globals::sWindowWidth / 2) {
		SetWorldRectX(player_ptr->GetWorldRectCenterX() - GetWorldRect()->w / 2);
	}
	if (player_ptr->GetWorldRectCenterY() > Globals::sWindowHeight / 2 && player_ptr->GetWorldRectCenterY() < level_ptr->GetLevelMaxPosY() - Globals::sWindowHeight / 2) {
		SetWorldRectY(player_ptr->GetWorldRectCenterY() - GetWorldRect()->h / 2);
	}
}
