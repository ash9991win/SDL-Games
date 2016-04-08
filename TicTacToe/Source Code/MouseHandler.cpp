#include"MouseHandler.h"
#include<iostream>
using namespace std;

MouseHandler::MouseHandler()
{
	mouse_coord = { 0, 0 };

}

//Handle the mouse event
void MouseHandler::handleEvent(SDL_Event e)
{
	switch (e.type)
	{
		
	
	case SDL_MOUSEBUTTONUP: isClicked = true;
		
		SDL_GetMouseState(&mouse_coord.x, &mouse_coord.y);
		break;
	case SDL_MOUSEBUTTONDOWN: isClicked = false;
		SDL_GetMouseState(&mouse_coord.x, &mouse_coord.y);
		break;
	
	case SDL_QUIT:
		SDL_Quit();
		exit(0);
	}
}
//Return isClicked
bool MouseHandler::checkClicked()
{
	return isClicked;
}
SDL_Point MouseHandler::getCoord()
{
	return mouse_coord;
}
//The following function determines the click position with regards to the board and returns an index
int MouseHandler::getIndexforClick()
{
	if (isClicked)
	{
		SDL_Rect mouse_rect;
		mouse_rect.x = mouse_coord.x;
		mouse_rect.y = mouse_coord.y;
		mouse_rect.w = 1;
		mouse_rect.h = 1;
		int rect_w = 180, rect_h = 180;
		int offset_x = 1,offset_y = 1;
		int rect_x = 22, rect_y = 22;
		int index = -1;
		for (int i = 1; i < 10; i++)
		{
			SDL_Rect tile_rect;
			if ((i) % 3 == 1 && (i)!= 1)
			{
				rect_x = 22;
				rect_y += 180;

			}
			
			tile_rect.x = rect_x;
			tile_rect.y = rect_y;
			tile_rect.w = 180;
			tile_rect.h = 180;
			SDL_Rect temp_rect;
			if (SDL_IntersectRect(&mouse_rect, &tile_rect,&temp_rect) )
			{
				index = i;
			}
			rect_x += 180;
			

		}
		if (index >= 1 && index < 10)
		{
			return index - 1;
		}
		else
			return -1;
	}
}
//The following function checks if the cursor is within a square in the board.
bool MouseHandler::withinBounds()
{
	SDL_GetMouseState(&mouse_coord.x, &mouse_coord.y);

	SDL_Rect mouse_rect;
	mouse_rect.x = mouse_coord.x;
	mouse_rect.y = mouse_coord.y;
	mouse_rect.w = 1;
	mouse_rect.h = 1;
	bool within_bounds = false;
	int rect_w = 180, rect_h = 180;
	int offset_x = 1, offset_y = 1;
	int rect_x = 22, rect_y = 22;
	int index = -1;
	for (int i = 1; i < 10; i++)
	{
		SDL_Rect tile_rect;
		if ((i) % 3 == 1 && (i) != 1)
		{
			rect_x = 22;
			rect_y += 180;

		}

		tile_rect.x = rect_x;
		tile_rect.y = rect_y;
		tile_rect.w = 180;
		tile_rect.h = 180;
		SDL_Rect temp_rect;
		if (SDL_IntersectRect(&mouse_rect, &tile_rect, &temp_rect))
		{
			within_bounds = true;
		}
		rect_x += 180;


	}
	return within_bounds;
}
//The following function returns a cell number when the cursor hovers over the board.
int MouseHandler::getIndexforHover()
{
	SDL_GetMouseState(&mouse_coord.x, &mouse_coord.y);
		SDL_Rect mouse_rect;
		mouse_rect.x = mouse_coord.x;
		mouse_rect.y = mouse_coord.y;
		mouse_rect.w = 1;
		mouse_rect.h = 1;
		int rect_w = 180, rect_h = 180;
		int offset_x = 1, offset_y = 1;
		int rect_x = 22, rect_y = 22;
		int index = -1;
		for (int i = 1; i < 10; i++)
		{
			SDL_Rect tile_rect;
			if ((i) % 3 == 1 && (i) != 1)
			{
				rect_x = 22;
				rect_y += 180;

			}

			tile_rect.x = rect_x;
			tile_rect.y = rect_y;
			tile_rect.w = 180;
			tile_rect.h = 180;
			SDL_Rect temp_rect;
			if (SDL_IntersectRect(&mouse_rect, &tile_rect, &temp_rect))
			{
				index = i;
			}
			rect_x += 180;


		}
		if (index >= 1 && index < 10)
		{
			return index - 1;
		}
		else
			return -1;
	}

