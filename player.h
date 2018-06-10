#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "loadTexture.h"
#include "collision.h"
#include "tile.h"
class Player
{
	public:
		static const int PLAYER_WIDTH = 20;
		static const int PLAYER_HEIGHT = 20;
		static const int PLAYER_VEL = 5;

		Player(SDL_Renderer* renderer);

		void handleEvent(SDL_Event& e);
		void move(Tile *tiles[], int levelWidth, int levelHeight);
		void render(SDL_Rect& camera);
		void objRender(int camX, int camY);
		int getPosX();
		int getPosY();

		SDL_Rect cameraMovement(SDL_Rect camera, int levelWidth, int levelHeight, int screenWidth, int screenHeight);

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
