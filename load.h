#ifndef LOAD_H
#define LOAD_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
SDL_Texture* loadTexture( std::string path,SDL_Renderer* gRenderer );
SDL_Surface* loadSurface(std::string path);

#endif