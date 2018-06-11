#ifndef WINDOW_H
#define WINDOW_H


#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

class LWindow
{
	public:
		LWindow();
		bool init();
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;
		SDL_Renderer* createRenderer();
		void handleEvent( SDL_Event& e, SDL_Renderer* gRenderer);
		void free();
		int getWidth();
		int getHeight();
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();

	private:
		SDL_Window* mWindow;
		int mWidth;
		int mHeight;
		bool mMouseFocus;
		bool mKeyboardFocus;
		bool mFullScreen;
		bool mMinimized;
};

#endif
