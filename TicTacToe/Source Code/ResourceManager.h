/**
TICTACTOE
This class is used as a generic resource loader. It has a constructor to initialize the SDL_image and SDL_ttf.
Author: Ashwin Sankaranarayanan
*/
#ifndef RESOURCE_H
#define RESOURCE_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<string>
using namespace std;
class ResourceLoader
{
public:
	ResourceLoader();
	SDL_Texture* loadimage(SDL_Renderer* prenderer, string filename);
	SDL_Texture* loadtext(SDL_Renderer* prenderer, TTF_Font* font, SDL_Color color, string text);
	void destroy(SDL_Texture* ptexture);
	int getHeight();
	int getWidth();
	~ResourceLoader();
private:
	SDL_Texture* mimagetexture, *mtexttexture;
	int mWidth, mHeight;
};
#endif