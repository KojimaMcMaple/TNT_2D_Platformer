#include "Game.h"
#include "TextElement.h"
#include <cstring>
using namespace std;

TextElement::TextElement(const int x, const int y, const char* str, const int sz, 
	const SDL_Color col): m_TextColor(col)
{
	strcpy_s(m_String, 64, str);
	this->SetPos(x, y);
	this->SetSize(sz);
}

TextElement::~TextElement()
{
	TTF_CloseFont(m_Font);
	SDL_DestroyTexture(m_pTexture);
}

void TextElement::Render()
{
	SDL_RenderCopy(TheGame::Instance()->getRenderer(), m_pTexture, 0, &m_rTextRect);
}

void TextElement::SetText(const char * str)
{
	strcpy_s(m_String, 64, str);
	SDL_Surface* fontSurf = TTF_RenderText_Solid(m_Font, m_String, m_TextColor);
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), fontSurf);
	m_rTextRect = { m_rTextRect.x, m_rTextRect.y, fontSurf->w, fontSurf->h };
	SDL_FreeSurface(fontSurf);
}

void TextElement::SetPos(const int x, const int y)
{
	m_rTextRect = { x, y, m_rTextRect.w, m_rTextRect.h };
}

void TextElement::SetSize(const int sz)
{
	if (m_Font != nullptr)
	{
		TTF_CloseFont(m_Font);
	}
	m_Font = TTF_OpenFont("../assets/textures/LTYPE.TTF", sz);
	this->SetText(m_String);
}

void TextElement::SetColor(const SDL_Color& col)
{
	m_TextColor = col;
	this->SetText(m_String);
}
