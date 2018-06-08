#include "main.h"
#include "load.h"
#include "player.h"
#include "ltimer.h"
#include "loadTexture.h"
#include "window.h"
#include <sstream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

LTexture gBGTexture;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gSceneTexture;
LWindow gWindow;


bool general::init()
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

		if( !gWindow.init())
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = gWindow.createRenderer();
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
void general::close()
{
	SDL_DestroyRenderer( gRenderer );
	gWindow.free();
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
bool general::loadMedia()
{
	bool success = true;
	gBGTexture.loadFromFile("images/bg.png", gRenderer);
	return success;
}

int main( int argc, char* args[])
{
	general general;
	general.init();
	general.loadMedia();
	bool quit = false;
	SDL_Event e;
	Player player(gRenderer);
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	while( !quit )
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
				quit = true;
			player.handleEvent(e);
			gWindow.handleEvent(e, gRenderer);
		}
		if(!gWindow.isMinimized())
		{
			player.move();
			camera = player.cameraMovement(camera);

			SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderClear( gRenderer );

			gBGTexture.render( 0, 0, &camera, gRenderer, NULL, NULL);

			player.objRender(camera.x,camera.y);

			SDL_RenderPresent(gRenderer);			
		}

	}
	general.close();
	return 0;
}
