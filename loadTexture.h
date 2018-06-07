#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
class LTexture{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
		void free();
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void render(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer);
		int getWidth();
		int getHeight();
	private:
		SDL_Texture * mTexture;
		int mWidth;
		int mHeight;


};
	