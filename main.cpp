#include <sstream>
#include "main.h"
#include "load.h"
#include "player.h"
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
	int frame = 0;
	SDL_Event e;
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;
	std::stringstream timeText;
	int currentTime = 0;
	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );
		SDL_Rect* currentClip = &playerClips[frame/12];
		playerSpriteSheetTexture.setColor(r/3,g,b);
		playerSpriteSheetTexture.render(100,100,currentClip, gRenderer);

		SDL_RenderPresent(gRenderer);

		++frame;
		if(frame/12 >= PLAYER_TOTAL)
		{
			frame = 0;
		}
		if(currentTime + SDL_GetTicks() == 1)
			printf("passed");
	}
	close();
	return 0;
}