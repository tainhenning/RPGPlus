#ifndef MAIN_H
#define MAIN_H
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

#include "globals.h"
#include "load.h"
#include "player.h"
#include "ltimer.h"
#include "loadTexture.h"
#include "window.h"
#include "tile.h"

class general{
	public:
		enum KeyPressSurfaces
		{
			KEY_PRESS_SURFACE_DEFAULT, 
			KEY_PRESS_SURFACE_UP,
			KEY_PRESS_SURFACE_DOWN, 
			KEY_PRESS_SURFACE_LEFT, 
			KEY_PRESS_SURFACE_RIGHT, 
			KEY_PRESS_SURFACE_TOTAL
		};
		bool init();
		bool loadMedia(Tile* tiles[]);
		void close(Tile* tiles[]);
		bool touchesWall(SDL_Rect box, Tile* tiles[]);
		bool setTiles(Tile* tiles[], std::string file);
		bool setTileGrass(Tile* tiles[], std::string file);

};
#endif
