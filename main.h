#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
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
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

#endif