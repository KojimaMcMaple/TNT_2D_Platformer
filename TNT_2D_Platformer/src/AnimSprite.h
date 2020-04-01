#pragma once

#include "AnimState.h"

class AnimSprite
{
private:
	AnimState anim_id_;
	int start_row_; 
	int start_col_;
	int num_frames_;
	float anim_speed_;
	bool is_looping_ = true;
	int max_sheet_row_;
	int max_sheet_col_;
public:
	AnimSprite();
	~AnimSprite();

	AnimState GetAnimId();
	int GetStartRow(); 
	int GetStartCol();
	int GetNumFrames();
	float GetAnimSpeed();
	bool IsLooping();
	int GetMaxSheetRow();
	int GetMaxSheetCol();

	void SetAnimId(AnimState value);
	void SetStartRow(int value);
	void SetStartCol(int value);
	void SetNumFrames(int value);
	void SetAnimSpeed(float value);
	void SetLooping(bool toggle);
	void SetMaxSheetRow(int value);
	void SetMaxSheetCol(int value);
};
