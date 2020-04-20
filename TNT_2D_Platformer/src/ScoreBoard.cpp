#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(const int x, const int y, const char* str, const int sz, const SDL_Color col)
	: TextElement(x, y, str, sz, col), m_score(0)
{
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::setScore(int score)
{
	m_score = score;
	string temp = "Score: " + to_string(score);
	SetText(temp.c_str());
}

int ScoreBoard::getScore()
{
	return m_score;
}
