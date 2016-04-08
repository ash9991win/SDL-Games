#include"ResourceManager.h"
#include<iostream>
using namespace std;
ResourceLoader::ResourceLoader()
{
	mimagetexture = 0;
	mWidth = 0;
	mHeight = 0;

}
//The following function loads an image given a renderer and a filename
SDL_Texture* ResourceLoader::loadimage(SDL_Renderer* prenderer, string filename)
{
	string temp_string = "Assets/images/" + filename;
	SDL_Surface* tempsurface = IMG_Load(temp_string.c_str());
	if (tempsurface != NULL)
	{


		SDL_Surface* convertsurface = SDL_ConvertSurface(tempsurface, tempsurface->format, NULL);
		SDL_Texture* temptexture = SDL_CreateTextureFromSurface(prenderer, convertsurface);
		mimagetexture = temptexture;

		mWidth = convertsurface->w;
		mHeight = convertsurface->h;

		return mimagetexture;
	}
	else
		return NULL;

}
//The following function returns a texture for an input text.
SDL_Texture* ResourceLoader::loadtext(SDL_Renderer* prenderer, TTF_Font* font, SDL_Color color, string text)
{
	SDL_Surface* tempsurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (tempsurface != NULL)
	{


		SDL_Surface* convertsurface = SDL_ConvertSurface(tempsurface, tempsurface->format, NULL);

		SDL_Texture* temptexture = SDL_CreateTextureFromSurface(prenderer, convertsurface);
		mtexttexture = temptexture;
		return mtexttexture;
	}
	//else
	//cout << TTF_GetError() << "ERR" << endl;
	return NULL;
}

int ResourceLoader::getHeight()
{
	return mHeight;
}
int ResourceLoader::getWidth()
{
	return mWidth;
}
void ResourceLoader::destroy()
{
	SDL_DestroyTexture(mimagetexture);
	SDL_DestroyTexture(mtexttexture);
	
}