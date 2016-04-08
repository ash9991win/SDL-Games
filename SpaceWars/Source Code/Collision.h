
/**
SPACE WARS 
This class is used to check collisions between two rectangles

Author: Ashwin Sankaranarayanan
*/#ifndef COLLISION_H
#define COLLISION_H
#include<SDL.h>
class Collider
{
public:
	/**
	Check if the two rectangles collide or no.
	Parameters: Two SDL_Rect for checking
	Return Values: TRUE if collided, else returns false
	*/
	bool checkCollision(SDL_Rect a,SDL_Rect b);


};
#endif