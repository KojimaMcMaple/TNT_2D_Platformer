#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__

enum GameObjectType {
	LEVEL,
	TILESET,
	TILE,
	PLAYER,
	ENEMY,
	PROP,
	ARROW,
	SCREEN,
	NUM_OF_TYPES
};

enum GameObjectInitType {
	WORLD_RECT,
	DST_RECT
};

#endif /* defined (__GAME_OBJECT_TYPE__) */