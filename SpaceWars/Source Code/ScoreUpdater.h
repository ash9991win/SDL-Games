/**
SPACE WARS 
This is a class to render the stat during the game. It is used to render the score and the missile count in the current gameloop

Author: Ashwin Sankaranarayanan
*/
#ifndef SCORE_H
#define SCORE_H
#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include<sstream>
using namespace std;
#include"ResourceManager.h"
class StatUpdater
{
public:
	/**
	A constructor to initialize the varialbes
	*/
	StatUpdater();
	/**
	Set the renderer for the current session
	Parameters: The Renderer for the current session
	*/
	void setRenderer(SDL_Renderer* prenderer);

	
	/**
	Draw onto the screen.
	Parameters: The X and Y coordinates and the string to be displayed
	*/
	void render(int posx,int posy,string data);
	/**
	Load the font parameters
	Parameters: The font type and its color
	*/
	void loadFont(TTF_Font* font, SDL_Color color);
	/**
	Set the transparency of the texture ( to create a blinking effect)
	Parameters: The Alpha value of the texture
	*/
	void setAlpha(int a);
	
private:
	
	/**
	The renderer for the current session
	*/
	SDL_Renderer* current_renderer;
	/**
	A ResourceLoader to convert the string to a texture
	*/
	ResourceLoader stat_loader;
	/**
	A texture for the stat
	*/
	SDL_Texture* menu_item2;
	/**
	The font properties
	*/
	TTF_Font* font;
	SDL_Color color;
	/**
	The Alpha value of the texture
	*/
	int alpha = 255;


};
#endif
