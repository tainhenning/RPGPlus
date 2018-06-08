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
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
		const int LEVEL_WIDTH = 1280;
		const int LEVEL_HEIGHT = 960;
		Player(SDL_Renderer* renderer);
		void handleEvent(SDL_Event& e);
		void move();
		void render();
		void objRender(int camX, int camY);
		int getPosX();
		int getPosY();
		SDL_Rect cameraMovement(SDL_Rect camera);
		LTexture playerUp[3];
		LTexture playerLeft[3];
		LTexture playerRight[3];
		LTexture playerDown[3];
		LTexture* currentAnimation[3];
	private:
		int mPosX, mPosY;
		int mVelX, mVelY;
		int frame;
		int frameBase;
		int frameEnd;
		SDL_Rect mCollider;
		LTexture* playerTexture;		
		SDL_Renderer* renderer;
};
#endif
