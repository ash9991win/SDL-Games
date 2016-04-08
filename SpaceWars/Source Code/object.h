/**
SPACE WARS

This is a generic object class, which can represent any object in the game. It is overriden for specific entities like asteroids and bullets. It has the generic functions.

Author: Ashwin Sankaranarayanan

*/#ifndef OBJECT_H
#define OBJECT_H
#include<SDL.h>
#include"ResourceManager.h"
class Object
{
public:
	/**
	Create a texture for a image given
	Parameters: The filename
	*/
	SDL_Texture* loadimage(string filename);
	/**
	Change the y-coordinate of the object
	*/
	void move();
	/**
	Handle any keyboard events
	Parameters: SDL_Event object
	*/
	void HandleEvent(SDL_Event& e);
	/**
	Set the renderer for the current session
	*/
	void setRenderer(SDL_Renderer* prenderer);
	/**
	Return the width of the image loaded
	Return Values: The width of the image
	*/
	int getWidth();
	/**
	Return the height of the image loaded
	Return Values: The height of the image
	*/
	int getHeight();
	/**
	Get the X coordinate of the image
	@reutrn The X coordinate
	*/
	int getX();
	/**
	Get the Y coordinate of the image
	Return Values: The Y coordinate
	*/
	int getY();
	/**
	Get the bounding box of the image
	Return Values: A SDL_Rect which bounds the image
	*/
	SDL_Rect getCollider();
	/**
	Set the X and Y coordinate of the object
	Parameters: The X and Y coordinate
	*/
	void setPosition(int x, int y);
	/**
	Draw the image onto the screen
	*/
	void render();
	/**
	Return the current speed of the object
	Return Values: The speed of the object
	*/
	int getSpeed();
	/**
	Set the current speed of the object
	Parameters: The current speed
	*/
	void setSpeed(int speed);
	/**
	Sets the window's dimension
	Parameters: The Width and the Height of the window
	*/
	void setWindowDimension(int W, int H);
	/**
	Destroy the textures and renderer
	*/
	void destroy();
protected:
	/**
	The X and Y coordinates
	*/
	float mPosx, mPosy;
	/**
	The X and Y velocities
	*/
	float mVelx, mVely;
	/**
	The renderer for the current session
	*/
	SDL_Renderer* current_renderer;
	/**
	A texture for the image
	*/
	SDL_Texture* mobjecttexture;
	/**
	A ResourceLoader object for loading the textures
	*/
	ResourceLoader mresourceloader;
	/**
	The window dimensions
	*/
	int window_width, window_height;
	/**
	A bounding box for the texture
	*/
	SDL_Rect collider;
	/**
	Width and height of the texture
	*/
	int mwidth, mheight;
	/**
	The speed at which the x and y velocites have to be changed
	*/
	int speed = 1;
};

#endif