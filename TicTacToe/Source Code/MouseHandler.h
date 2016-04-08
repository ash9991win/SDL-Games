/**
TICTACTOE
This class is used to handle the mouse input
Author: Ashwin Sankaranarayanan
*/
#ifndef MOUSE_H
#define MOUSE_H
#include<SDL.h>
#include"ResourceManager.h"
class MouseHandler
{
private:
	/*
	mouse_coord --> Store the X and Y positions of the mouse
	isClicked    -> Set if there is a click event
	*/
	SDL_Point mouse_coord;
	bool isClicked;
	

public:
	MouseHandler();
	void handleEvent(SDL_Event e);
	SDL_Point getCoord();
	bool checkClicked();
	int getIndexforClick();
	bool withinBounds();
	
	int getIndexforHover();
	
};
#endif