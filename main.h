#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class general{
	public:
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
};


#endif
