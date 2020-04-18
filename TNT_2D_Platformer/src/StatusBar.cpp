#include "StatusBar.h"
#include "Game.h"

StatusBar::StatusBar(SDL_Rect* hostDst, int maxHealth) : m_maxHealth(maxHealth)
{
	m_Dst = { hostDst->x, hostDst->y - 5, hostDst->w, 5 };
	m_health = m_maxHealth;
}

void StatusBar::update(SDL_Rect* hostDst)
{
	m_Dst = { hostDst->x, hostDst->y - 5, hostDst->w, 5 };
	
	// Do something here if some conditions are met

}

void StatusBar::draw()
{
	// Stores the old color to restore afterwards
	SDL_Color oldColor;
	SDL_GetRenderDrawColor(TheGame::Instance()->getRenderer(), &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);

	// Render status bar
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &m_Dst);
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 255, 0, 255);
	SDL_Rect dst = { m_Dst.x, m_Dst.y, static_cast<int>(m_Dst.w * m_health / m_maxHealth), 5 };
	SDL_RenderFillRect(TheGame::Instance()->getRenderer(), &dst);

	// Restore previous render color
	SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), oldColor.r, oldColor.g, oldColor.b, oldColor.a);
}

void StatusBar::changeHealth(int change)
{
	m_health += change;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	if (m_health < 0)
	{
		m_health = 0;
	}
}

void StatusBar::SetHealth(int value)
{
	m_health = value;
	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	if (m_health < 0)
	{
		m_health = 0;
	}
}
