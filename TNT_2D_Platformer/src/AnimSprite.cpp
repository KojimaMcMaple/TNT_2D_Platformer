#include "AnimSprite.h"

AnimSprite::AnimSprite()
{
}

AnimSprite::~AnimSprite()
{
}

AnimState AnimSprite::GetAnimId()
{
	return anim_id_;
}

int AnimSprite::GetStartCol()
{
	return start_col_;
}

int AnimSprite::GetStartRow()
{
	return start_row_;
}

int AnimSprite::GetNumFrames()
{
	return num_frames_;
}

int AnimSprite::GetMaxSheetCol()
{
	return max_sheet_col_;
}

void AnimSprite::SetAnimId(AnimState value)
{
	anim_id_ = value;
}

void AnimSprite::SetStartCol(int value)
{
	start_col_ = value;
}

void AnimSprite::SetStartRow(int value)
{
	start_row_ = value;
}

void AnimSprite::SetNumFrames(int value)
{
	num_frames_ = value;
}

void AnimSprite::SetMaxSheetCol(int value)
{
	max_sheet_col_ = value;
}
