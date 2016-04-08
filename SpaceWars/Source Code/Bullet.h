/**
SPACE WARS

This class is used to represent the bullets which are fired by the player.

Author: Ashwin Sankaranarayanan
*/#ifndef BULLET_H
#define BULLET_H
#include<SDL.h>
#include<string>
#include"ResourceManager.h"
#include"object.h"

using namespace std;

static int BULLET_VEL = 10;

//Inherit from the Object class
class Bullet : public Object
	{
		/* The class for bullets*/
	public:
		/**
		Constructor. Initializes the variables
		*/
		Bullet();

		
		/**
		THe move() method of the Object class is overriden because, unlike the generic object class which increments the Y-coordinate, the bullet has to go up. hence its Y-coordinate should decrease

		*/
		void move();
		/**
		Draw the image onto the screen
		*/
		void render();

		/**
		Sets the RENDER flag.
		Parameters: BOOL value for the RENDER flag
		*/
		void setRenderFlag(bool render_flag);
		/**
		Get the RENDER flag
		Return Values: BOOL value of the flag
		*/
		bool getRenderFlag();
		/**
		Reset the coordinates and flags
		*/
		void reset();
		/**
		Set the HIT flag
		*/
		void setHit(bool flag);
	protected:
		/**
		The damage of the bullet
		*/
		int  mdamage;
		/**
		The HIT flag to determine whether it has been 
		*/
		bool isHit = false;

		/**
		The RENDER flag to check whether to render or no
		*/
		bool render_flag = true;

	};
#endif
