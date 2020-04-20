#include "GameObject.h"
#include "Game.h"

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

void GameObject::Animate()
{
	auto anim_db = GetAnimList()[anim_state_];
	int animationRate = round(anim_db->GetNumFrames() / 2 / anim_db->GetAnimSpeed());
	if (TheGame::Instance()->getFrames() % animationRate == 0)
	{
		if (checking_anim_state_ != anim_state_) { //Just changed state
			checking_anim_state_ = anim_state_;
			curr_frame_ = 0;
			SetPlayedAnimSfx(false);
			//if (anim_state_ == ATTACK) {
			//	std::cout << "RESET SOUND\n";
			//}
		}
		// PROCESS VISUAL ANIM
		if (curr_frame_ > anim_db->GetNumFrames() - 1) {
			if (anim_db->IsLooping()) {
				curr_frame_ = 0;
			}
			else {
				curr_frame_ = anim_db->GetNumFrames() - 1;
			}
		}
		curr_col_ = anim_db->GetStartCol() + curr_frame_;
		if (curr_col_ > anim_db->GetMaxSheetCol() - 1) {
			//curr_col_ -= anim_db->GetMaxSheetCol();
			curr_col_ %= anim_db->GetMaxSheetCol();
		}
		// if frame exceeds GetMaxSheetCol, go to the next row
		curr_row_ = anim_db->GetStartRow() + (int)((curr_frame_+ anim_db->GetStartCol()) / anim_db->GetMaxSheetCol()); //bug fixed: must add anim_db->GetStartCol() to curr_frame_ because GetStartCol is an offset
		
		// SET SRC, if GetFrameH or GetFrameW equals -1, there is one sprite sheet
		if (anim_db->GetFrameH() == -1) {
			setSrcY(curr_row_ * getSrc()->h);
		}
		else {
			setSrcY(curr_row_ * anim_db->GetFrameH());
		}

		if (anim_db->GetFrameW() == -1) {
			setSrcX(curr_col_ * getSrc()->w);
		}
		else {
			setSrcX(curr_col_ * anim_db->GetFrameW());
		}

		// PROCESS ATK HITBOX
		if (curr_frame_ == anim_db->GetAtkStartFrame()) {
			is_atk_hit_box_active_ = true;
		}
		if (curr_frame_ == anim_db->GetAtkEndFrame()) {
			is_atk_hit_box_active_ = false;
		}

		curr_frame_++;
	}
}

int GameObject::GetHP()
{
	return hp_;
}

int GameObject::GetMaxHP()
{
	return max_hp_;
}

int GameObject::GetAtkPower()
{
	return atk_power_;
}

SDL_Rect* GameObject::GetWorldRect()
{
	return &world_rect_;
}

int GameObject::GetWorldRectRightmostX()
{
	return world_rect_.x+world_rect_.w;
}

int GameObject::GetWorldRectLowermostY()
{
	return world_rect_.y + world_rect_.h;
}

int GameObject::GetWorldRectCenterX()
{
	return Util::XCenterRect(&world_rect_);
}

int GameObject::GetWorldRectCenterY()
{
	return Util::YCenterRect(&world_rect_);
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

bool GameObject::IsHitBoxVisible()
{
	return is_hit_box_visible_;
}

SDL_Rect* GameObject::GetAtkHitBox()
{
	return &atk_hit_box_;
}

bool GameObject::IsAtkHitBoxActive()
{
	return is_atk_hit_box_active_;
}

int GameObject::GetIFrames()
{
	return i_frames_;
}

SDL_Rect* GameObject::GetSightRect()
{
	return &sight_rect_;
}

bool GameObject::IsGrounded()
{
	return is_grounded_;
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

int GameObject::getCurrFrame()
{
	return curr_frame_;
}

int GameObject::getCurrRow()
{
	return curr_row_;
}

int GameObject::getCurrCol()
{
	return curr_col_;
}

bool GameObject::HasChangedState()
{
	if (checking_anim_state_ != anim_state_) { //Just changed state
		checking_anim_state_ = anim_state_;
		//curr_frame_ = 0;
		has_played_anim_sfx_ = false;
		return true;
	}
	return false;
}

bool GameObject::HasEndedAnimation()
{
	if (checking_anim_state_ == anim_state_) {
		if (getCurrFrame() == GetAnimList()[getAnimState()]->GetNumFrames()) { //anim ended, GetNumFrames()-1 WILL SKIP THE LAST FRAME OF ANIM
			return true;
		}
	}
	
	return false;
	//return animationEnded;
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

bool GameObject::IsCollidable()
{
	return is_collidable_;
}

AnimState GameObject::getAnimState()
{
	return anim_state_;
}

std::vector<AnimSprite*>& GameObject::GetAnimList()
{
	return anim_list_;
}

bool GameObject::HasPlayedAnimSfx()
{
	return has_played_anim_sfx_;
}

GameObjectType GameObject::getType()
{
	return m_type;
}

void GameObject::SetHP(int value)
{
	hp_ = value;

	if (hp_ < 0) {
		hp_ = 0;
	}
}

void GameObject::SetMaxHP(int value)
{
	max_hp_ = value;
}

void GameObject::SetAtkPower(int value)
{
	atk_power_ = value;
}

void GameObject::SetWorldRect(int x, int y, int w, int h)
{
	world_rect_ = { x,y,w,h };
}

void GameObject::SetWorldRectX(int coord)
{
	world_rect_.x = coord;
}

void GameObject::SetWorldRectY(int coord)
{
	world_rect_.y = coord;
}

void GameObject::setSrc(SDL_Rect src_rect)
{
	src_ = { src_rect.x,src_rect.y,src_rect.w,src_rect.h };
}

void GameObject::setSrc(int x, int y, int w, int h)
{
	src_ = { x,y,w,h };
}

void GameObject::setSrcX(int coord)
{
	src_.x = coord;
}

void GameObject::setSrcY(int coord)
{
	src_.y = coord;
}

void GameObject::setDst(SDL_Rect dst_ptr)
{
	dst_ = dst_ptr;
}

void GameObject::setDst(int x, int y, int w, int h)
{
	dst_ = { x,y,w,h };
}

void GameObject::setDstX(int coord)
{
	dst_.x = coord;
}

void GameObject::setDstY(int coord)
{
	dst_.y = coord;
}

void GameObject::SetWorldXAndHitBox(int coord)
{
	world_rect_.x = coord;
	setHitBoxX(GetWorldRectCenterX() - (getHitBoxW() / 2) + getHitBoxOffsetX()); //center hitbox and then apply offset
}

void GameObject::SetWorldYAndHitBox(int coord)
{
	world_rect_.y = coord;
	setHitBoxY(GetWorldRectCenterY() - (getHitBoxH() / 2) + getHitBoxOffsetY()); //center hitbox and then apply offset
}

void GameObject::SetHitBoxXAndWorld(int coord)
{
	hit_box_.x = coord;
	SetWorldRectX(getHitBoxCenterX() - getHitBoxOffsetX() - (GetWorldRect()->w / 2)); //center world_rect_ to hitbox, factoring in offset
}

void GameObject::SetHitBoxYAndWorld(int coord)
{
	hit_box_.y = coord;
	SetWorldRectY(getHitBoxCenterY() - getHitBoxOffsetY() - (GetWorldRect()->h / 2)); //center world_rect_ to hitbox, factoring in offset
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

void GameObject::SetHitBoxVisibility(bool toggle)
{
	is_hit_box_visible_ = toggle;
}

void GameObject::SetAtkHitBox(int x, int y, int w, int h)
{
	atk_hit_box_ = { x,y,w,h };
}

void GameObject::SetAtkHitBoxX(int value)
{
	atk_hit_box_.x = value;
}

void GameObject::SetAtkHitBoxY(int value)
{
	atk_hit_box_.y = value;
}

void GameObject::SetAtkHitBoxActive(bool toggle)
{
	is_atk_hit_box_active_ = toggle;
}

void GameObject::SetIFrames(int value)
{
	i_frames_ = value;
}

void GameObject::SetSightRect(int x, int y, int w, int h)
{
	sight_rect_.x = x;
	sight_rect_.y = y;
	sight_rect_.w = w;
	sight_rect_.h = h;
}

void GameObject::SetSightRectX(int value)
{
	sight_rect_.x = value;
}

void GameObject::SetSightRectY(int value)
{
	sight_rect_.y = value;
}

void GameObject::SetGrounded(bool toggle)
{
	is_grounded_ = toggle;
}

void GameObject::setTextureId(std::string id)
{
	texture_id_ = id;
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

void GameObject::SetCollidable(bool toggle)
{
	is_collidable_ = toggle;
}

void GameObject::setType(GameObjectType newType)
{
	m_type = newType;
}

void GameObject::setCurrFrame(int value)
{
	curr_frame_ = value;
}

void GameObject::setCurrRow(int value)
{
	curr_row_ = value;
}

void GameObject::setCurrCol(int value)
{
	curr_col_ = value;
}

void GameObject::setAnimState(AnimState newState)
{
	anim_state_ = newState;
	animationEnded = false;
}

void GameObject::PlayAnimSfx(SoundId sfx)
{
	if (HasPlayedAnimSfx() == false) {
		if (checking_anim_state_ == anim_state_) {
			TheSoundManager::Instance()->playSound(sfx, 0); //sound
			SetPlayedAnimSfx(true);
		}
	}
}

void GameObject::InitAnimList()
{
	for (int i = 0; i < NUM_OF_ANIM_STATES; i++) {
		anim_list_.push_back(new AnimSprite());
	}
}

void GameObject::SetPlayedAnimSfx(bool toggle)
{
	has_played_anim_sfx_ = toggle;
}

void GameObject::setAcceleration(glm::vec2 newAcceleration)
{
	m_acceleration = newAcceleration;
}
