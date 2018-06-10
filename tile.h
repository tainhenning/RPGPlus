#ifndef TILE_H
#define TILE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "collision.h"
#include "loadTexture.h"
class Tile
{
	private:
		int mType;
		SDL_Rect mBox;
	public:
		Tile(int x, int y, int tileType, int tileWidth, int tileHeight);
		void show();
		int getType();
		SDL_Rect getBox();
		void trender(SDL_Rect& camera,SDL_Rect tileClips[12], SDL_Renderer* rend, LTexture tileTexture);
};


#endif