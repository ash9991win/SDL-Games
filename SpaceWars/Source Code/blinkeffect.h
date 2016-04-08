/**
SPACE WARS
This class is used for rendering a plain image onto the screen. Unlike the other classes ( like Asteroid or the Player class) this does not have a move function. It  just renders the image at a specified position. An optional function is to set a timer for rendering the image.


Author: Ashwin Sankaranayanan
*/
#ifndef BLINK_H
#define BLINK_H
#include<SDL.h>
#include"ResourceManager.h"
#include"object.h"
#include"Timer.h"
/**
Inherit from the Object class.*/
class EffectManager : public Object
{
public:
	/**
	Set the coordinates of the image to be rendered.
	Parameters: X and Y coordinates.
	*/
	void setDimension(int w, int h);
	/**
	Set the time for rendering
	Parameters: Interger value of the time in seconds.
	*/
	void setTime(int sec);
	/**
	Render the image onto the screen
	*/
	void render();
	/**
	Create the texture for the string passed.
	Parameters: The string for which a texture is to be created
	*/
	void loadtext(string text);
	/**
	Create a texture  for an image.
	Parameters: The filename for which to create a texture
	*/
	void loadimage(string filename);
	/**
	Initialize the font and color of the text
	*/
	void loadfont(TTF_Font* font, SDL_Color color);
	/**
	Start the timer
	*/
	void start();
	/**
	Stop the timer
	*/
	void stop();
	/**
	Delete all textures and renderer.
	*/
	void destroy();
private:
	//A Timer class object for the texture
	Timer effect_timer;
	//The texture variable
	SDL_Texture* effect_texture;
	
	//The font variable
	TTF_Font* font;
	//The color variable
	SDL_Color color;
	//The timer interval variable
	int time_sec;


};
#endif