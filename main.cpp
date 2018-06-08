#include "main.h"
#include "load.h"
#include "player.h"
#include "ltimer.h"
#include "loadTexture.h"
LTexture gBGTexture;
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

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	gBGTexture.loadFromFile("images/bg.png", gRenderer);
	return success;
}

int main( int argc, char* args[] )
{
	init();
	loadMedia();
	bool quit = false;
	SDL_Event e;
	Player player(gRenderer);
	SDL_Rect wall;
	wall.x = 300;
	wall.y = 40;
	wall.w = 40;
	wall.h = 400;
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
				quit = true;
			player.handleEvent(e);
		}
		//Center the camera over the dot
		camera.x = ( player.getPosX() + Player::PLAYER_WIDTH / 2 ) - SCREEN_WIDTH / 2;
		camera.y = ( player.getPosY() + Player::PLAYER_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

		//Keep the camera in bounds
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
		wall.x = -camera.x + 400;
		wall.y = -camera.y + 40;
		player.move(wall);

		SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear( gRenderer );

		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );

		gBGTexture.render( 0, 0, &camera, gRenderer, NULL, NULL);
		SDL_RenderDrawRect( gRenderer, &wall );

		player.objRender(camera.x,camera.y);

		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}
