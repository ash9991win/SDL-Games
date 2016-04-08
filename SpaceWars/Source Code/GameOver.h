/**
SPACE WARS
This class is to represent the game over screen

Author: Ashwin Sankaranarayanan
*/
#include<SDL.h>
#include"ResourceManager.h"
#include"menuloader.h"
/**
Three constant varialbes corresponding to one choice that the player makes
*/
const int REPLAY_GAME = 1;
const int MAIN_MENU = 3;
const int SAVE_SCORE = 2;
/**
Inherit from the MainMenu class. The Gameover menu is essentially a modified version of the MainMenu. So it is inherited so that the basic functionality remains the same
*/
class Gameover : public Mainmenu
{

public:
	/**
	Constructor to initialize the variables
	*/
	Gameover();
	/**
	The score to be displayed in the game over screen is set here
	Parameters: The final score of the player
	*/
	void setScore(int score);
	/**
	Set the name of the player
	Parameters: The name of the player
	*/
	void setName(string name);
	/**
	Write the player and his score onto the file
	*/
	void write();
	/**
	Load the font and the color of the font. This is overriden from the MainMenu as a different colored font is used to render the mainmenu
	*/
	void loadfont(TTF_Font* font, SDL_Color color);
	
	/**
	Render the menu. It is overriden as the contents of the menu  varies from that of the mainmenu
	*/
	void render();
private:
	/**
	The name of the player
	*/
	string name;
	/**
	The score of the player
	*/
	int score;


};
