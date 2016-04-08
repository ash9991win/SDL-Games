/**
SPACE WARS

This class is for the SaveMenu item. 
*/#ifndef SAVE_H
#define SAVE_H
#include"menuloader.h"
#include"FileManager.h"
/**
Inherit from the MainMenu class.
*/
class SaveData : public Mainmenu
{
public:
	/**
	Override the render method of MainMenu to draw the current menu
	*/
	void render();
	/**
	Override the handleEvent of MainMenu as in this current menu, the player has to enter the name etc
	*/
	void handleEvent(SDL_Event &e);
	/**
	Override the LoadFont method 
	*/
	void loadfont(TTF_Font* font, SDL_Color color);
	/**
	Set the score of the player
	Parameters: The score of the player
	*/
	void setScore(int score);
	/**
	Clear all the selections and scores
	*/
	void reset(); 
	/**
	Destroy the textures and renderers
	*/
	void destroy();

private:
	
	/**
	The texture for the player's name
	*/
	SDL_Texture* name_texture;
	/**
	A render flag to check whether to render the text or no
	*/
	bool renderText;
	/**
	The name to be entered
	*/
	string inputText =" ";
	/**
	A FileHandler object to store the name of the player and their score
	*/
	FileHandler file_handler;
	/**
	The score of the player
	*/
	int score;

};

#endif