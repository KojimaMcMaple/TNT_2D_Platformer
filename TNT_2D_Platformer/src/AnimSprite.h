#pragma once

#include "AnimState.h"

class AnimSprite
{
private:
	AnimState anim_id_;
	int start_col_;
	int start_row_;
	int num_frames_;
	int max_sheet_col_;
public:
	AnimSprite();
	~AnimSprite();

	AnimState GetAnimId();
	int GetStartCol();
	int GetStartRow();
	int GetNumFrames();
	int GetMaxSheetCol();

	void SetAnimId(AnimState value);
	void SetStartCol(int value);
	void SetStartRow(int value);
	void SetNumFrames(int value);
	void SetMaxSheetCol(int value);
};
