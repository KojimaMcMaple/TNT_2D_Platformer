#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(int x, int y, int w, int h, int init_type = WORLD_RECT)
{
	if (init_type == WORLD_RECT) {
		SetWorldRect(x, y, w, h);
	}
	else {
		setDst(x, y, w, h);
	}
}

Tile::Tile(int x, int y, int w, int h, char tile_char, int init_type = WORLD_RECT)
{
	GetWorldRect()->x = x;
	GetWorldRect()->y = y;
	GetWorldRect()->w = w;
	GetWorldRect()->h = h;
	tile_char_ = tile_char;
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::draw()
{
}

void Tile::clean()
{
}

char Tile::GetTileChar()
{
	return tile_char_;
}

int Tile::GetTileTextureId()
{
	return tile_texture_id_;
}

void Tile::SetTileTextureId(int id)
{
	tile_texture_id_ = id;
}

Tile* Tile::getUp()
{
	return m_pNeighbours[UP];
}

Tile* Tile::getDown()
{
	return m_pNeighbours[DOWN];
}

Tile* Tile::getRight()
{
	return m_pNeighbours[RIGHT];
}

Tile* Tile::getLeft()
{
	return m_pNeighbours[LEFT];
}

void Tile::setUp(Tile* tile)
{
	m_pNeighbours[UP] = tile;
}

void Tile::setDown(Tile* tile)
{
	m_pNeighbours[DOWN] = tile;
}

void Tile::setRight(Tile* tile)
{
	m_pNeighbours[RIGHT] = tile;
}

void Tile::setLeft(Tile* tile)
{
	m_pNeighbours[LEFT] = tile;
}