/// TITLE SCREEN MANAGEMENT

#ifndef __TITLE_H__
#define __TITLE_H__

#include "UIManager.h"

enum class TitleMenuState
{
	TITLE,
	NEWGAME,
	CONFIG,
	QUIT
};


class TitleText : public UIManager
{
public:
	TitleText();
	~TitleText();
	
	void setTextPos();
	void change_text(TitleMenuState cur_state);
	void draw() override;
};


class TitleMenu : public UIManager
{
private:
	TitleText* _t_text;
	TitleMenuState _cur_state;

public:
	TitleMenu();
	~TitleMenu();

	void draw() override;

	// Getter
	TitleText* GetText();
	TitleMenuState GetMenuState();

	// Setter
	void SetMenuState(TitleMenuState cur_state);
};

#endif // __TITLE_H__
