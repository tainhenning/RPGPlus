#include "player.h"
Player::Player(SDL_Renderer* rend)
{
	mPosX = 100;
	mPosY = 100;
	mVelX = 0;
	mPosY = 0;
	frame = 0;
	mCollider.w = PLAYER_WIDTH;
	mCollider.h = PLAYER_HEIGHT;
	renderer = rend;

	playerRight[0].loadFromFile("images/playerFrames/playerside21.png",renderer);
	playerRight[1].loadFromFile("images/playerFrames/playerside22.png",renderer);
	playerRight[2].loadFromFile("images/playerFrames/playerside23.png",renderer);
	playerLeft[0].loadFromFile("images/playerFrames/playerside1.png",renderer);
	playerLeft[1].loadFromFile("images/playerFrames/playerside2.png",renderer);
	playerLeft[2].loadFromFile("images/playerFrames/playerside3.png",renderer);
	playerDown[0].loadFromFile("images/playerFrames/playerfront1.png",renderer);
	playerDown[1].loadFromFile("images/playerFrames/playerfront2.png",renderer);
	playerDown[2].loadFromFile("images/playerFrames/playerfront3.png",renderer);
	playerUp[0].loadFromFile("images/playerFrames/playerback1.png",renderer);
	playerUp[1].loadFromFile("images/playerFrames/playerback2.png",renderer);
	playerUp[2].loadFromFile("images/playerFrames/playerback3.png",renderer);

	for (int i = 0; i < 3; ++i)
	{
		currentAnimation[i] = &playerDown[0];
	}
	playerTexture = currentAnimation[0];
}

void Player::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: 
				mVelY -= PLAYER_VEL;
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerUp[i];
				}
				break;
			case SDLK_DOWN: 
				mVelY += PLAYER_VEL;
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerDown[i];
				}				
				break;
			case SDLK_LEFT: 
				mVelX -= PLAYER_VEL; 
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerLeft[i];
				}				
				break;
			case SDLK_RIGHT:
				mVelX += PLAYER_VEL; 
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerRight[i];
				}
				break;
		}
	}
	else if(e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: 
				mVelY = 0;
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerUp[0];
				} 
				break;
			case SDLK_DOWN: 
				mVelY = 0; 
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerDown[0];
				} 
				break;
			case SDLK_LEFT: 
				mVelX = 0; 
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerLeft[0];
				} 
				break;
			case SDLK_RIGHT: 
				mVelX = 0; 
				for (int i = 0; i < 3; ++i)
				{
					currentAnimation[i] = &playerRight[0];
				} 
				break;
		}
	}
}

void Player::move()
{
	Collision collider;
	mPosX += mVelX;
	mCollider.x = mPosX;
	if((mPosX < 0) || (mPosX + PLAYER_WIDTH > LEVEL_WIDTH))
	{
		mPosX -= mVelX;		
		mCollider.x = mPosX;
	}
	mPosY += mVelY;
	mCollider.y = mPosY;

	if((mPosY < 0) || (mPosY + PLAYER_HEIGHT > LEVEL_HEIGHT))
	{
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
	playerTexture = currentAnimation[frame/6];
	++frame;
	if(frame/6 >= 3)
		frame = 0;
}

void Player::objRender(int camX, int camY)
{
	playerTexture->render(mPosX - camX, mPosY - camY, NULL, renderer, NULL, NULL);
}

int Player::getPosX()
{
	return mPosX;
}

int Player::getPosY()
{
	return mPosY;
}

SDL_Rect Player::cameraMovement(SDL_Rect camera)
{
	camera.x = ( mPosX + Player::PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
	camera.y = ( mPosY + Player::PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;
	if( camera.x < 0 )
	{ 
		camera.x = 0;
	}
	if( camera.y < 0 )
	{
		camera.y = 0;
	}
	if( camera.x > LEVEL_WIDTH - camera.w )
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if( camera.y > LEVEL_HEIGHT - camera.h )
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}	
	return camera;
}
