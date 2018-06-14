#include "tile.h"

Tile::Tile(int x, int y, int tileType, int tileWidth, int tileHeight)
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = 48;
	mBox.h = 48;

	mType = tileType;
}

void Tile::trender(SDL_Rect& camera, SDL_Rect tileClips[12], SDL_Renderer* rend, LTexture tileTexture)
{
	Collision collider;
	if(collider.checkCollision(camera, mBox))
	{
		tileTexture.render(mBox.x - camera.x, mBox.y - camera.y,&tileClips[mType], rend,NULL,NULL);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

void Tile::setBoxX(int x)
{
	mBox.x = x;
}
void Tile::setBoxY(int y)
{
	mBox.y = y;

}
