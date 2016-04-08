/**
SPACE WARS

This is the Player class which holds all the information about the spaceship controlled by the player

Author: Ashwin Sankaranarayanan'
*/
#ifndef PLAYER_H
#define PLAYER_H
#include<SDL.h>
#include<string>
#include"ScoreUpdater.h"
#include"object.h"
#include"ResourceManager.h"

using namespace std;
/**
A constant variable for the velocity of the player
*/
static int PLAYER_VEL = 10;
static bool FIRED = false;
/**
Inherit from the Object class for the generic methods like SetRenderer and GetX,GetY etc
*/
class Player : public Object
{
public:
	/**
	A constructor to initialze the player
	Parameters: The health and the shield of the player
	*/
	Player(int health, int shield);
	/**
	Get the player's current health
	Return Values: The health of the player
	*/
	int getHealth();
	/**
	Get the current shield of the player
	Return Values: The shild of the player
	*/
	int getShield();
	/**
	Draw the player onto the screen
	*/
	void render();
	/**
	Sets the hit flag
	*/
	void isHit();
	
	/**
	Move the player object by changing the X and Y coordinates
	*/
	void move();
	/**
	Handle the keyboard events
	*/
	void HandleEvent(SDL_Event& e);
	
	/**
	Returns the ammo of the player
	Return Values: The ammo left
	*/
	int getBulletCount();
	/**
	Generate a texture for the image passed
	Parameters: The filename of the image
	*/
	SDL_Texture* loadimage(string file);
	
	
	/**
	Reset the player's health and shield
	Parameters: The new health and shield of the player
	*/
	
	void reset(int health,int shield);
	/**
	Set the health of the player
	Parameters: The health of the player
	*/
	void setHealth(int health);
	/**
	Set the shield of the player
	Parameters: The shield of the player
	*/
	void setShield(int shield);
	
	
	
	
	/**
	Returns the LOCK flag
	Return Values: The BOOL value of the flag
	*/
	bool getLockFlag();
	/**
	Set the LOCK flag. This flag is used to lock the player's movement when it has collided with the asteroid
	Parameters: The BOOL value of the LOCK flag
	*/
	void setLockFlag(bool flag);
	/**
	Destroy the texture and renderer
	*/
	void destroy();

protected:
	/**
	The health of the player
	*/
	int mHealth;
	/**
	The shield of the player
	*/
	int mShield;
	/**
	The ammo of the player
	*/
	int bullet_count;
	/**
	A rectangle representing the health of the player
	*/
	SDL_Rect Hrect;
	/**
	A rectangle representing the shield of the player
	*/
	SDL_Rect Srect;
	/**
	A texture for the shield
	*/
	SDL_Texture* shield_texture;
	/**
	A LOCK flag which prevents the player from moving
	*/
	bool lock_move_flag;
	

};


#endif
