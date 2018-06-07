#include "player.h"

Dot::Dot(SDL_Renderer* rend)
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mPosY = 0;
	frame = 0;
	renderer = rend;
	dotTexture.loadFromFile("images/playerFrames/playerback1.png", renderer);
	
	playerFrames[PLAYER_BACK1].loadFromFile("images/playerFrames/playerback1.png", renderer);
	playerFrames[PLAYER_BACK2].loadFromFile("images/playerFrames/playerback2.png", renderer);
	playerFrames[PLAYER_BACK3].loadFromFile("images/playerFrames/playerback3.png", renderer);
	playerFrames[PLAYER_FRONT1].loadFromFile("images/playerFrames/playerfront1.png", renderer);
	playerFrames[PLAYER_FRONT2].loadFromFile("images/playerFrames/playerfront2.png", renderer);
	playerFrames[PLAYER_FRONT3].loadFromFile("images/playerFrames/playerfront3.png", renderer);
	playerFrames[PLAYER_LEFT1].loadFromFile("images/playerFrames/playerside1.png", renderer);
	playerFrames[PLAYER_LEFT2].loadFromFile("images/playerFrames/playerside2.png", renderer);
	playerFrames[PLAYER_LEFT3].loadFromFile("images/playerFrames/playerside3.png", renderer);
	playerFrames[PLAYER_RIGHT1].loadFromFile("images/playerFrames/playerside21.png", renderer);
	playerFrames[PLAYER_RIGHT2].loadFromFile("images/playerFrames/playerside22.png", renderer);
	playerFrames[PLAYER_RIGHT3].loadFromFile("images/playerFrames/playerside23.png", renderer);

}

void Dot::handleEvent(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch(e.key.keysym.sym)
		{
			case SDLK_UP: 
				mVelY -= DOT_VEL; 
				break;
			case SDLK_DOWN: 
				mVelY += DOT_VEL;
				break;
			case SDLK_LEFT: 
				mVelX -= DOT_VEL; 
				break;
			case SDLK_RIGHT:
				mVelX += DOT_VEL; 
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

void Dot::move()
{

	mPosX += mVelX;
	if((mPosX < 0) || (mPosX + DOT_WIDTH >1920))
	{
		mPosX -= mVelX;		
	}
	mPosY += mVelY;
	if((mPosX < 0) || (mPosY + DOT_HEIGHT > 1080))
	{
		mPosY -= mVelY;
	}
	dotTexture = playerFrames[frame/12];
	frame++;
	if(frame/12 >= PLAYER_TOTAL)
		frame = 0;
}

int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
}

void Dot::objRender()
{
	dotTexture.render(mPosX, mPosY, NULL, renderer);
}