#ifndef COLLISION_H
#define COLLISION_H
#pragma once

#include <SDL.h>

class Collision
{
	public:
		bool checkCollision(SDL_Rect a, SDL_Rect b);

};
#endif