#ifndef GLOBALS_H
#define	GLOBALS_H
#pragma once
#include <SDL.h>
#include "tile.h"

class globals
{
	public:
		void setTileSet(Tile* tileset[12]);
		Tile* tileset[12];
};
#endif