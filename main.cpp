#include <sstream>
#include "main.h"
#include "load.h"
#include "player.h"
#include "ltimer.h"
#include "loadTexture.h"
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

SDL_Rect playerClips[PLAYER_TOTAL];

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

bool loadMedia()
{
	bool success = true;
	for(int i = 0; i<PLAYER_TOTAL;i++)
	{
		playerClips[i].x = 0;
		playerClips[i].y = i*25;
		playerClips[i].w = 16;
		playerClips[i].h = 24;
	}

	return success;
}



int main( int argc, char* args[] )
{
	init();
	loadMedia();
	bool quit = false;

	SDL_Event e;

	Dot dot(gRenderer);
	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
				quit = true;
			dot.handleEvent(e);
		}
		SDL_PollEvent(&e);

		SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear( gRenderer );
		
		dot.objRender();
		dot.move();
		
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}
