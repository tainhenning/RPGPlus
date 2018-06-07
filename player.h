#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "loadTexture.h"

class Dot
{
	public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int DOT_VEL = 5;
		LTexture dotTexture;
		Dot(SDL_Renderer* renderer);
		void handleEvent(SDL_Event& e);
		void move();
		void render();
		int getPosX();
		int getPosY();
		void objRender();
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		int frame;
		SDL_Renderer* renderer;
		enum playerFramesEnum
		{
			PLAYER_BACK1,
			PLAYER_BACK2,
			PLAYER_BACK3,
			PLAYER_FRONT1,
			PLAYER_FRONT2,
			PLAYER_FRONT3,
			PLAYER_LEFT1,
			PLAYER_LEFT2,
			PLAYER_LEFT3,
			PLAYER_RIGHT1,
			PLAYER_RIGHT2,
			PLAYER_RIGHT3,
			PLAYER_TOTAL
		};
		LTexture playerFrames [PLAYER_TOTAL]; 
};
#endif
