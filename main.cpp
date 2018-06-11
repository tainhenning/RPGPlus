#include "general.h"
#include <fstream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FRAMES_PER_SECOND = 20;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;

SDL_Event event;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
LTexture gTileTexture;
LTexture gBGTexture;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gSceneTexture;
LWindow gWindow;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

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
bool general::loadMedia(Tile* tiles[])
{
	bool success = true;
	if(!gBGTexture.loadFromFile("images/bg.png", gRenderer))
	{
		printf("Failed to load background texture\n");
		success = false;
	}
	if(!gTileTexture.loadFromFile("images/tiles.png", gRenderer))
	{
		printf("Failed to load tile texture\n");
		success = false;
	}
	if(!setTiles(tiles, "maps/lazy.map"))
	{
		printf("Failed to load tile set!\n");
		success = false;
	}

	return success;
}
bool general::setTiles(Tile* tiles[], std::string file)
{
	bool tilesLoaded = true;
	int x = 0, y = 0;
	std::ifstream map(file);
	if(!map.is_open())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			int tileType = -1;

			map >> tileType;

			if(map.fail())
			{
				printf("ERROR loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}
			if((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType, TILE_WIDTH, TILE_HEIGHT);
			}
			else
			{
				printf("Eror loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}
			x += TILE_WIDTH;

			if(x >= LEVEL_WIDTH)
			{
				x = 0;
				y += TILE_HEIGHT;
			}
		}
		if(tilesLoaded)
		{
			gTileClips[ TILE_RED ].x = 0;
			gTileClips[ TILE_RED ].y = 0;
			gTileClips[ TILE_RED ].w = TILE_WIDTH;
			gTileClips[ TILE_RED ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 80;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_BLUE ].x = 0;
			gTileClips[ TILE_BLUE ].y = 160;
			gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
			gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPLEFT ].x = 80;
			gTileClips[ TILE_TOPLEFT ].y = 0;
			gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_LEFT ].x = 80;
			gTileClips[ TILE_LEFT ].y = 80;
			gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMLEFT ].x = 80;
			gTileClips[ TILE_BOTTOMLEFT ].y = 160;
			gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOP ].x = 160;
			gTileClips[ TILE_TOP ].y = 0;
			gTileClips[ TILE_TOP ].w = TILE_WIDTH;
			gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

			gTileClips[ TILE_CENTER ].x = 160;
			gTileClips[ TILE_CENTER ].y = 80;
			gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
			gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOM ].x = 160;
			gTileClips[ TILE_BOTTOM ].y = 160;
			gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPRIGHT ].x = 240;
			gTileClips[ TILE_TOPRIGHT ].y = 80;
			gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_RIGHT ].x = 240;
			gTileClips[ TILE_RIGHT ].y = 80;
			gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
			gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
			gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;						
		}
	}
	map.close();
	return tilesLoaded;
}
void general::close(Tile* tiles[])
{
	SDL_DestroyRenderer( gRenderer );
	gWindow.free();
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[])
{
	Tile* tiles[TOTAL_TILES];
	general general;
	general.init();
	if(!general.loadMedia(tiles))
		printf("failed to load media!\n");

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
			if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_SPACE: 
						general.setTiles(tiles, "maps/lazy2.map");
				}
			}
			player.handleEvent(e);
			gWindow.handleEvent(e, gRenderer);
		}
		if(!gWindow.isMinimized())
		{
			player.move(tiles, LEVEL_WIDTH, LEVEL_HEIGHT);
			camera = player.cameraMovement(camera, LEVEL_WIDTH, LEVEL_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

			SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff);
			SDL_RenderClear( gRenderer );

			gBGTexture.render( 0, 0, &camera, gRenderer, NULL, NULL);

			for(int i = 0; i < TOTAL_TILES; ++i)
			{
				gTileTexture.render( tiles[i]->getBox().x - camera.x,  tiles[i]->getBox().y - camera.y, &gTileClips[tiles[i]->getType()], gRenderer,NULL,NULL);
			}
			player.objRender(camera.x,camera.y);

			SDL_RenderPresent(gRenderer);			
		}

	}
	general.close(tiles);
	return 0;
}
