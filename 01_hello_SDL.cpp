/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT, 
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN, 
	KEY_PRESS_SURFACE_LEFT, 
	KEY_PRESS_SURFACE_RIGHT, 
	KEY_PRESS_SURFACE_TOTAL
};
bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gHelloWorld = NULL;



bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Cannot load image! Error: %s\n", SDL_GetError());
	}
	return loadedSurface;
}

bool loadMedia()
{
	bool success = true;

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./images/press.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]== NULL)
		success = false;
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./images/left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]== NULL)
		success = false;	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./images/right.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]== NULL)
		success = false;	
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./images/up.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]== NULL)
		success = false;
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./images/down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]== NULL)
		success = false;

	return success;
}

void close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if(!init())
	{
		printf("Initialization Failed\n");
	}
	else
	{
		if(!loadMedia())
		{
			printf("Media Failed\n");
		}
		else
		{			
			bool quit = false;
			SDL_Event e;
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					switch(e.key.keysym.sym)
					{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;
					}
				}
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}


	close();

	return 0;
}