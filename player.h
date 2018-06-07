#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
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
SDL_Texture* playerSprites[PLAYER_TOTAL];
void playerInit()
{
};