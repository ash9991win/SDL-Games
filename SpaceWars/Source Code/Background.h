/**
SPACE WARS
Background.h
This class is used to describe the scrolling background

Author: Ashwin Sankaranarayanan
*/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include<string>
using namespace std;
#include"ResourceManager.h"
class Background
{
public:
	/**
	Constructor for initialzing the variables
	*/
	Background();
	/**
	Render the given image at the coordinates specified.
	Parameters: The coordinates at which to render the image
	*/
	void render(int x,int y);
	/**
	Sets the renderer for the current session.
	Parameters: A SDL_Renderer* for the current session
	*/
	void setRenderer(SDL_Renderer* prenderer);
	/**
	Sets the background texture based on the filename
	Parameters: The filename of the image to render as background
	*/
	void loadimage(string filename);
	/**
	Get the scroll offset
	Return Values: The scroll offset
	*/
	int getScroll();
	/**
	Get the width of the background image
	Return Values: The width of the image
	*/
	int getWidth();
	/**
	Get the height of the background image
	Return Values: The height of the image
	*/
	int getHeight();
	/**
	Get the speed of the background. Here speed is the speed at which the Y coordinate changes for the scrolling effect.
	Return Values: The scrolling speed.
	*/
	int getSpeed();
	/**
	Set the window dimensions so that the image can be rendered accordingly.
	Parameters: The width and height of the window
	*/
	void setDimension(int width, int height);
	/**
	Sets the speed at which the background changes
	Parameters: The speed of the background
	*/
	void setSpeed(int speed);
	
	/**
	Destroy all the textures and renderers
	*/
	void destroy();
private:
	SDL_Texture* background;     // The texture for the background image
	ResourceLoader bg_loader;	//  A ResourceLoader to obtain the SDL_Texture for the image
	int maxwidth, maxheight;    // Dimensions of the window
	int scrolloffset;           // The offset for scrolling. 
	int mwidth, mheight;        // The dimensions of the image
	SDL_Renderer* current_renderer; // The renderer for the current session.
	int background_speed = 1;    // The speed of the background image.
	int window_width, window_height;

};

#endif