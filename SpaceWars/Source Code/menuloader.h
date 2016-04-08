/**
SPACE WARS

This is a generic menu class. It is used for the main menu display ( and is inherited for the other menus like gameover menu).

Author: Ashwin Sankaranarayanan
*/
#ifndef MENU_LOADER
#define MENU_LOADER
#include<SDL.h>
#include<SDL_ttf.h>
#include"ResourceManager.h"
/**
Constant integers representing each selection
*/
const int PLAY_GAME = 1;
const int QUIT_GAME = 3;
const int STATS = 2;

class Mainmenu
{
public:
	/**
	Constructor to initialize the variables
	*/
	Mainmenu();
	/**
	Returns the currently selected option
	Return Values: The current selection
	*/
	int getSelection();
	/**
	Handle the keyboard events
	Parameters: An SDL_Event
	*/
	 void handleEvent(SDL_Event &e);
	 /**
	 Set the current renderer for the session
	 Parameters: SDL_Renderer
	 */
	void setRenderer(SDL_Renderer* prenderer);
	/**
	Draw the menuu onto the screen
	*/
	 void render();
	 /**
	 Set the font and its color
	 Parameters: The font and the color
	 */
	 void loadfont(TTF_Font* font, SDL_Color color);

	 /**
	 Reset the variables
	 */
	void reset();
	/**
	Destroy all the textures and renderer
	*/
	void destroy();
protected:
	/**
	The destination rectangle. The rectangle onto which the menu is to be drawn
	*/
	SDL_Rect* destrect;
	/**
	The title rectangle. The rectangle representing the title of the menu
	*/
	SDL_Rect title_rect;
	/**
	A texture for the first menu item
	*/
	SDL_Texture* menu_item1;
	/**
	A texture for the second menu item
	*/
	SDL_Texture* menu_item2;
	/**
	A texture for the third menu item
	*/
	SDL_Texture* menu_item3;
	/**
	A texture for the title of the menu
	*/
	SDL_Texture* title_texture;
	/**
	The font of the menu
	*/
	TTF_Font* font;
	/**
	The color of the font
	*/
	SDL_Color color;
	/**
	The renderer for the current session
	*/
	SDL_Renderer* currentrenderer;
	/**
	The resource loader for the menu items
	*/
	ResourceLoader itemloader;
	/**
	The current selection (ie where the arrow keys have stopped at)
	*/
	int current_selection;
	/**
	Final selection. The selection when the enter key was pressed
	*/
	int finalselection;


};

#endif
