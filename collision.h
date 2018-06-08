#ifndef COLLISION_H
#define COLLISION_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
class Collision
{
	public:
		bool checkCollision(SDL_Rect a, SDL_Rect b);

};
#endif