#include "UI.h"
#include "Game.h"

UI::UI(std::string texture_id, std::string texture_path, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int dst_w, int dst_h)
{
	setTextureId(texture_id);
	TheTextureManager::Instance()->load(texture_path, getTextureId(), TheGame::Instance()->getRenderer());
	setSrc(src_x, src_y, src_w, src_h);
	setDst(dst_x, dst_y, dst_w, dst_h);
	setType(GameObjectType::SCREEN);
}

UI::~UI()
{
}

void UI::update()
{
}

void UI::draw()
{
	TheTextureManager::Instance()->draw(TheGame::Instance()->getRenderer(), getTextureId(), getSrc(), getDst(), 0.0, 0, SDL_FLIP_NONE);
}

void UI::clean()
{
}
