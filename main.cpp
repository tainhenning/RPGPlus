#include "general.h"
#include <fstream>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int FRAMES_PER_SECOND = 20;

const int LEVEL_WIDTH = 1440;
const int LEVEL_HEIGHT = 1440;

const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const int TOTAL_TILES = 900;
const int TOTAL_TILE_SPRITES = 12;

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
SDL_Rect gTileClips[30];

int currentTiles = 0;
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
	if(!gTileTexture.loadFromFile("images/dungeon_tiles.png", gRenderer))
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
	currentTiles = 1;
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
			for (int i = 0; i < 30; ++i)
			{
				gTileClips[i].y = (i%3)*48;
				gTileClips[i].w = TILE_WIDTH;
				gTileClips[i].h = TILE_HEIGHT;
			}
			gTileClips[ 0 ].x = 0;
			gTileClips[ 1 ].x = 0;
			gTileClips[ 2 ].x = 0;
			gTileClips[ 3 ].x = 48;
			gTileClips[ 4 ].x = 48;
			gTileClips[ 5 ].x = 48;
			gTileClips[ 6 ].x = 96;
			gTileClips[ 7 ].x = 96;
			gTileClips[ 8 ].x = 96;
			gTileClips[ 9 ].x = 144;
			gTileClips[ 10 ].x = 144;
			gTileClips[ 11 ].x = 144;
			gTileClips[ 12 ].x = 192;					
			gTileClips[ 13 ].x = 192;					
			gTileClips[ 14 ].x = 192;					
			gTileClips[ 15 ].x = 240;					
			gTileClips[ 16 ].x = 240;					
			gTileClips[ 17 ].x = 240;					
			gTileClips[ 18 ].x = 288;					
			gTileClips[ 19 ].x = 288;					
			gTileClips[ 20 ].x = 288;					
			gTileClips[ 21 ].x = 336;					
			gTileClips[ 22 ].x = 336;					
			gTileClips[ 23 ].x = 336;				

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

bool switchToLevel2(Tile* tiles[])
{
	general general;
	if(currentTiles != 2)
	{
		general.setTiles(tiles, "maps/lazy1.map");
		currentTiles = 2;
	}
	else
		return false;
	return true;
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

			if(player.move(tiles, LEVEL_WIDTH, LEVEL_HEIGHT) == 1)
				switchToLevel2(tiles);
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