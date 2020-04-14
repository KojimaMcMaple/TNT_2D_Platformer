#pragma once

#include "AnimState.h"
#include <string>

class AnimSprite
{
private:
	std::string texture_id_ = ""; //texture_id_ from GameObject
	AnimState anim_id_;
	int start_row_; 
	int start_col_;
	int frame_width_ = -1; //src->w for entity w/ multi sheets, -1 will not modify src rect w
	int frame_height_ = -1; //src->h for entity w/ multi sheets, -1 will not modify src rect h
	int num_frames_;
	float anim_speed_;
	bool is_looping_ = true;
	int max_sheet_row_;
	int max_sheet_col_;
	int atk_start_frame_ = -1;
	int atk_num_frames_ = 0;

public:
	AnimSprite();
	~AnimSprite();

	std::string GetSpriteTextureId();
	AnimState GetAnimId();
	int GetStartRow(); 
	int GetStartCol();
	int GetFrameW(); 
	int GetFrameH();
	int GetNumFrames();
	float GetAnimSpeed();
	bool IsLooping();
	int GetMaxSheetRow();
	int GetMaxSheetCol();
	int GetAtkStartFrame();
	int GetAtkEndFrame();
	int GetAtkNumFrames();

	void SetSpriteTextureId(std::string value);
	void SetAnimId(AnimState value);
	void SetStartRow(int value);
	void SetStartCol(int value);
	void SetFrameW(int value);
	void SetFrameH(int value);
	void SetNumFrames(int value);
	void SetAnimSpeed(float value);
	void SetLooping(bool toggle);
	void SetMaxSheetRow(int value);
	void SetMaxSheetCol(int value);
	void SetAtkStartFrame(int value);
	void SetAtkNumFrames(int value);
};
