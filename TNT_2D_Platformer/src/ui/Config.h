#ifndef __CONFIGMENU_H__
#define __CONFIGMENU_H__

#include "UIManager.h"

class ConfigFullScreen :public UIManager {
public:
	ConfigFullScreen();
	~ConfigFullScreen();

	void SetFullScreenPos(int dst_x, int dst_y);
	void draw() override;
};

class Config_4x3 :public UIManager {
public:
	Config_4x3();
	~Config_4x3();

	void Set4x3Pos(int dst_x, int dst_y);
	void draw() override;
};

class Config_1x1 :public UIManager {
public:
	Config_1x1();
	~Config_1x1();

	void Set1x1Pos(int dst_x, int dst_y);
	void draw() override;
};

class Config_16x9 :public UIManager {
public:
	Config_16x9();
	~Config_16x9();

	void Set16x9Pos(int dst_x, int dst_y);
	void draw() override;
};

class Config_21x9 :public UIManager {
public:
	Config_21x9();
	~Config_21x9();

	void Set21x9Pos(int dst_x, int dst_y);
	void draw() override;
};

class ConfigTick :public UIManager {
public:
	ConfigTick();
	~ConfigTick();

	void SetTickPos(int dst_x, int dst_y);
	void draw() override;
};

class ConfigChosen :public UIManager {
public:
	ConfigChosen();
	~ConfigChosen();

	void SetChosenPos(int dst_x, int dst_y);
	void draw() override;
};

class ConfigRatioText :public UIManager {
public:
	ConfigRatioText();
	~ConfigRatioText();

	void SetRatioTextPos(int dst_x, int dst_y);
	void draw() override;
};

class ConfigMenu :public UIManager {
private:
	ConfigFullScreen* _c_fullscreen;
	ConfigRatioText* _c_ratiotext;
	Config_4x3* _c_4x3;
	Config_1x1* _c_1x1;
	Config_16x9* _c_16x9;
	Config_21x9* _c_21x9;
	ConfigTick* _c_tick_ratio;
	ConfigTick* _c_tick_fullscreen;
	ConfigChosen* _c_cursor;

	
public:
	ConfigMenu();
	~ConfigMenu();

	int _c_cursor_pos;
	
	void ExecuteCmd();
	void SetCursorPos();
	void SetConfigPos();
	
	void draw() override;

};

#endif // __CONFIGMENU_H__