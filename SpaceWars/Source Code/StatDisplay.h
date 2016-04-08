/**
SPACE WARS
This class is used to display the highscores saved in the file
*/#ifndef STAT_H
#define STAT_H
#include<map>
#include<vector>
using namespace std;
#include"menuloader.h"
#include"FileManager.h"
#include<sstream>
/**
Inherit from the MainMenu class ( as it is also a varied form of a menu)
*/
class StatDisplay : public Mainmenu
{
public:
	/**
	Override the Render function of MainMenu as the contents of this menu vary
	*/
	void render();
	/**
	Unlike the arrow keys in MainMenu,we need to handle backspace in this menu. So override the method of MainMenu
	Parameters: The SDL_Event
	*/
	void handleEvent(SDL_Event &e);
	/**
	Load the font and its color
	Parameters: The font type and its color
	*/
	void loadfont(TTF_Font* font, SDL_Color color);
	/**
	Set the dimension of the window
	Parameters: The dimensions of the window
	*/
	void setDimension(int w, int h);

private:

	/**
	A vector of textures for the data found in the file
	*/
	vector<SDL_Texture*> score_texture;
	/**
	A vector of the score and the player data read from the file
	*/
	vector<::pair<string,int>> texture_data;

	
	/**
	A FileHandler object to read the file data
	*/
	FileHandler file_handler;
	/**
	An array of rectangles, with each element corresponding to a single line in the file
	*/
	SDL_Rect* stat_rect;
	/**
	A temporary placeholder 
	*/
	SDL_Texture* temp_texture;
	/**
	The window dimensions
	*/
	int maxwidth, maxheight;


};

#endif