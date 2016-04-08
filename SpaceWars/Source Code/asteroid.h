/*
SPACE WARS
asteroid.h
The following class is used to describe the objects traveling across the screen, e.g : Asteroids and Power-Ups.

Author: Ashwin Sankaranarayanan

*/
#ifndef ASTEROID_H
#define ASTEROID_H
#include"ResourceManager.h"
class Space
{
public:
	/**
	Initialize all the varialbes 
	*/
	Space();
	/**
	Set the Coordinates of the object
	Parameters: The X and Y coordinates
	*/
	void setPosition(int x, int y);
	/**
	Sets the renderer to draw onto
	Parameters: The pointer to SDL_Renderer for the current session
	*/
	void setRenderer(SDL_Renderer* prenderer);
	/**
	Draws the objects onto the renderer
	*/
	void render();
	/**
	Changes the coordinates of the object
	*/
	void  move();
	/**
	Returns the X coordinate
	Return Values: the X coordinate
	*/
	int  getX();
	/**
	Returns the Y coordinate
	Return Values: the Y coordinate
	*/
	int  getY();
	/**
	Return the width of the texture
	Return Values: The Width
	*/
	int  getWidth();
	/**
	Return the height of the texture
	Return Values: the height
	*/
	int  getHeight();
	/**
	Loads the texture from the filename
	Parameters: THe filename
	*/
	void loadimage(string filename);
	/**
	Returns the bounding box of the object. I have used rectangular collision detection.
	Return Values: SDL_Rect describing the bounding boxes
	*/
	SDL_Rect getCollider();
	/**
	Set the HIT flag
	Parameters: Bool value of the flag
	*/
	void setHit(bool hit);
	/**
	Return the HIT flag
	Return Values: BOOL value of the flag*/
	bool getHit();
	bool istexture();
	/**
	Set the RENDER flag
	Parameters: Bool value of the flag
	*/
	void setRenderFlag(bool render);
	/**
	Get the RENDER flag
	Return Values: RENDER Flag
	*/
	bool getRenderFlag();
	/**
	Set the speed of the object
	Parameters: The speed
	*/
	void setVelocity(int velocity);
	/**
	Return the speed of the object
	Return Values: The speed
	*/
	int  getVelocity();
	
	/**
	Reset all the attributes (X and Y coordinates, Speed etc)
	*/
	void reset();
	/**
	Destroy all the textures and renderer
	*/
	void destroy();
private:

	int mPosx, mPosy, mwidth, mheight; //The coordinates and the dimensions of the image
	double rotate;                     //The angle by which to rotate the image
	SDL_Renderer* currentrenderer;     //The renderer of the session
	SDL_Texture* mobjecttexture;       //The SDL_Texture which is obtained for the image
	ResourceLoader mobjectloader;      //A resource loader object for getting a texture for the image
	SDL_Rect collider;                 //A rectangle bounding box for the image
	bool isHit;						   // HIT flag
	bool texture_present;             
	bool ifrender = true;              //Render flag 
	int velocity = 4;                  //The speed of the object
};
#endif