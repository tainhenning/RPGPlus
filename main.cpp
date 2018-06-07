#include <sstream>
#include "main.h"
#include "load.h"
#include "player.h"
#include "ltimer.h"
#include "loadTexture.h"

SDL_Rect playerClips[PLAYER_TOTAL];
LTexture playerSpriteSheetTexture;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
	playerSpriteSheetTexture.loadFromFile("images/playerSheet.png",gRenderer);

	for(int i = 0; i<PLAYER_TOTAL;i++)
	{
		playerClips[i].x = 0;
		playerClips[i].y = i*24;
		playerClips[i].w = 16;
		playerClips[i].h = 24;
	}

	return success;
}

void close()
{
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	init();
	loadMedia();
	playerInit();
	bool quit = false;
	int playerFrame = 0;
	int prevPlayerFrame = 0;
	int playerFrameSet = 0;
	int playerFrameMax = 0;
	int frame = 0;
	SDL_Event e;
	LTimer fpsTimer;
	fpsTimer.start();
	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						playerFrame = 0;
						prevPlayerFrame = playerFrame;
						playerFrameSet = 0;
						playerFrameMax = 3;
						break;
					case SDLK_DOWN:
						playerFrame = 3;
						prevPlayerFrame = playerFrame;
						playerFrameSet = 3;
						playerFrameMax = 3;
						break;
					case SDLK_LEFT:
						playerFrame = 3;
						prevPlayerFrame = playerFrame;
						playerFrameSet = 6;
						playerFrameMax = 3;
						break;
					case SDLK_RIGHT:
						playerFrame = 3;
						prevPlayerFrame = playerFrame;
						playerFrameSet = 9;
						playerFrameMax = 3;
						break;
				}

			}
			else if(e.type == SDL_KEYUP)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						playerFrame = 0;
						playerFrameSet = 0;
						playerFrameMax = 0;
						break;
					case SDLK_DOWN:
						playerFrame = 3;
						playerFrameSet = 3;
						playerFrameMax = 0;
						break;
					case SDLK_LEFT:
						playerFrame = 6;
						playerFrameSet = 6;
						playerFrameMax = 0;
						break;
					case SDLK_RIGHT:
						playerFrame = 9;
						playerFrameSet = 9;
						playerFrameMax = 0;
						break;
				}

			}
		}

		float avgFPS = frame/(fpsTimer.getTicks()/1000.f);
		if(avgFPS > 2000000)
			avgFPS = 0;

		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
		SDL_RenderClear( gRenderer );

		SDL_Rect* currentClip = &playerClips[(playerFrame)/6 + playerFrameSet];
		playerSpriteSheetTexture.render(100,100,currentClip, gRenderer);

		SDL_RenderPresent(gRenderer);

		++playerFrame;
		++frame;

		if(playerFrame/6 >= playerFrameMax)
		{
			playerFrame = prevPlayerFrame;
		}

	}
	close();
	return 0;
}
