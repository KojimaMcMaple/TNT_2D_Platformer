#include "Tile.h"

Tile::Tile()
{
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