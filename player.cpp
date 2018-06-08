#include "player.h"
Player::Player(SDL_Renderer* rend)
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mPosY = 0;
	mCollider.w = PLAYER_WIDTH;
	mCollider.h = PLAYER_HEIGHT;
	renderer = rend;
	playerTexture.loadFromFile("images/playerFrames/playerback1.png", renderer);
}

void Player::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: 
				mVelY -= PLAYER_VEL; 
				break;
			case SDLK_DOWN: 
				mVelY += PLAYER_VEL;
				break;
			case SDLK_LEFT: 
				mVelX -= PLAYER_VEL; 
				break;
			case SDLK_RIGHT:
				mVelX += PLAYER_VEL; 
				break;
		}
	}
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: 
				mVelY = 0; 
				break;
			case SDLK_DOWN: 
				mVelY = 0; 
				break;
			case SDLK_LEFT: 
				mVelX = 0; 
				break;
			case SDLK_RIGHT: 
				mVelX = 0; 
				break;
		}
	}
}

void Player::move(SDL_Rect& wall)
{
	Collision collider;
	mPosX += mVelX;
	mCollider.x = mPosX;
	if((mPosX < 0) || (mPosX + PLAYER_WIDTH >1280) || collider.checkCollision(mCollider, wall))
	{
		mPosX -= mVelX;		
		mCollider.x = mPosX;
	}
	mPosY += mVelY;
	mCollider.y = mPosY;

	if((mPosY < 0) || (mPosY + PLAYER_HEIGHT > 960) || collider.checkCollision(mCollider, wall))
	{
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}

void Player::objRender(int camX, int camY)
{
	playerTexture.render(mPosX - camX, mPosY - camY, NULL, renderer, NULL,NULL);
}

int Player::getPosX()
{
	return mPosX;
}

int Player::getPosY()
{
	return mPosY;
}