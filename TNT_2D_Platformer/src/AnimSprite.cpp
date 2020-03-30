#include "AnimSprite.h"

AnimSprite::AnimSprite()
{
}

AnimSprite::AnimSprite(AnimState anim_id, int start_row, int start_col, int num_frames, int max_sheet_row, int max_sheet_col)
{
	anim_id_ = anim_id;
	start_row_ = start_row;
	start_col_ = start_col;
	num_frames_ = num_frames;
	max_sheet_row_ = max_sheet_row;
	max_sheet_col_ = max_sheet_col;
}

AnimSprite::~AnimSprite()
{
}

AnimState AnimSprite::GetAnimId()
{
	return anim_id_;
}

int AnimSprite::GetStartRow()
{
	return start_row_;
}

int AnimSprite::GetStartCol()
{
	return start_col_;
}

int AnimSprite::GetNumFrames()
{
	return num_frames_;
}

int AnimSprite::GetMaxSheetRow()
{
	return max_sheet_row_;
}

int AnimSprite::GetMaxSheetCol()
{
	return max_sheet_col_;
}

void AnimSprite::SetAnimId(AnimState value)
{
	anim_id_ = value;
}

void AnimSprite::SetStartRow(int value)
{
	start_row_ = value;
}

void AnimSprite::SetStartCol(int value)
{
	start_col_ = value;
}

void AnimSprite::SetNumFrames(int value)
{
	num_frames_ = value;
}

void AnimSprite::SetMaxSheetRow(int value)
{
	max_sheet_row_ = value;
}

void AnimSprite::SetMaxSheetCol(int value)
{
	max_sheet_col_ = value;
}
