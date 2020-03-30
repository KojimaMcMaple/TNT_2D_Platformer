#pragma once

#include "AnimState.h"

class AnimSprite
{
private:
	AnimState anim_id;
	int start_col;
	int start_row;
	int num_frames;
	int max_sheet_col;
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
