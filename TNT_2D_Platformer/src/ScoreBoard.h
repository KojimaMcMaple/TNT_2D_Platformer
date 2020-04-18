#pragma once
#include "TextElement.h"
class ScoreBoard :
	public TextElement
{
private:
	int m_score;
public:
	ScoreBoard(const int x, const int y, const char* str,
		const int sz, const SDL_Color col = { 255, 255, 255, 255 });
	~ScoreBoard();
	void setScore(int score);
	int getScore();

};

