#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "loadTexture.h"
#include "collision.h"

class Player
{
	public:
		static const int PLAYER_WIDTH = 20;
		static const int PLAYER_HEIGHT = 20;
		static const int PLAYER_VEL = 5;
		Player(SDL_Renderer* renderer);
		void handleEvent(SDL_Event& e);
		void move(SDL_Rect& wall);
		void render();
		void objRender(int camX, int camY);
		int getPosX();
		int getPosY();
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		int frame;
		int frameBase;
		int frameEnd;
		SDL_Rect mCollider;
		LTexture playerTexture;		
		SDL_Renderer* renderer;
};
#endif
