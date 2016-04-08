/**
SPACE WARS
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
	/**
	A constructor to initialize the variables
	*/
	ResourceLoader();
	/**
	Return a SDL_Texture for the given image
	Return Values: A SDL_Texture for the image
	Parameters: The renderer of the current session and the filename of the image
	*/
	SDL_Texture* loadimage(SDL_Renderer* prenderer, string filename);
	/**
	Returns a SDL_Texture for a given text
	Return Values: A SDL_Texure for a given string
	Parameters: The renderer for the current session, the font parameters and the string for which texture is generated
	*/
	SDL_Texture* loadtext(SDL_Renderer* prenderer, TTF_Font* font, SDL_Color color, string text);
	/**
	Destroy all the textures
	*/
	void destroy();
	/**
	Get the height of the texture
	Return Values: The height of the texture
	*/
	int getHeight();
	/**
	Get the width of the texture
	Return Values: The width of the texture
	*/
	int getWidth();
	
private:
	/**
	One texture each of an image and a text
	*/
	SDL_Texture* mimagetexture, *mtexttexture;
	/**
	Dimensions of the texture
	*/
	int mWidth, mHeight;
};
#endif