/*
Space Wars 

This is the main loop of the game. 

Space Wars was inspired by top down space shooters which were prevalent in the early arcade games. I decided to combine it with the endless game genres prevalent now. The aim is simple, either navigate betweeen the asteroids or shoot them. If the player loses, a game over screen is displayed.
The option to save the score is also present, which writes the scores in binary to a file. The high scores option from mainmenu, displays the highest scores saved. If a name already exists in the file, then the highest score is the one displayed.

The random algorithm is a binary based algorithm. A six digit binary string is taken in, and the asteroids are renderered for all the 1's present in it. For example, if the number is 100001, then there will be two asteroids - one at the left and one at the right.

Author: Ashwin Sankaranarayanan



*/
#include"Player.h"
#include"ResourceManager.h"
#include"Background.h"
#include"asteroid.h"
#include"Collision.h"
#include"menuloader.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<math.h>
#include <bitset>
#include"GameOver.h"
#include"ScoreUpdater.h"
#include"Bullet.h"
#include"blinkeffect.h"
#include<sstream>
#include"SaveData.h"
#include"AudioManager.h"
#include"StatDisplay.h"
#include"Timer.h"

//The global variables
SDL_Window* gwindow = 0;
SDL_Surface* gsurface = 0;
SDL_Texture* gtexture = 0;
static SDL_Renderer* grenderer = 0;
TTF_Font* gfont = NULL;
SDL_Color gcolor;
SDL_Color gblue = { 0, 163, 202, 0xff };
//

//The user-defined variables for various components of the system
AudioManager audio_manager;
Player player(100, 50);
Mainmenu mainmenu;
Gameover gameover;
StatDisplay statDisplay;
Background background;
Space  asteroid_group[2][6];
Space powerUp_health, powerUp_shield, powerUp_ammo;
StatUpdater score_updater;
StatUpdater missile_updater;
Bullet temp_bullet;
vector<Bullet> bullets;
Timer score_timer;
StatUpdater hit_bonus;
Timer blink_timer;
EffectManager hit_effect;
EffectManager pause_effect;
Timer speed_timer;
SaveData save_menu;
Collider collider;

bool isMute = false;
SDL_Rect* lane_rect;
SDL_Rect free_rect;
vector<string> pattern;
int glane_no = 6;
bool quit = false;
int no_lane = glane_no;
SDL_Event e;
int scroll = 0;
bool inMenu = true, gameover_menu = true;
int start_time;
int MAX_WIDTH = 640, MAX_HEIGHT = 660;
int time_count = 0;
SDL_Rect game_rect = { 0, 0, 640, 620 };
SDL_Rect stat_rect = { 600, 0, 640, 40 };
bool full_screen;
TTF_Font* score_font;
stringstream score;
int hit_points = 0;
int final_score;
int ammo_count = 100;
bool fired = false;
//Function declarations
bool init();

void playgame(); 

void savegamedata();
void statdisplay();
void game_over();
void close();
// This function initialzies SDL framework
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_JPG | IMG_INIT_PNG))
		{
			TTF_Init();
			gwindow = SDL_CreateWindow("Space Wars", 10, 10, MAX_WIDTH, MAX_HEIGHT, SDL_WINDOW_SHOWN);    //Create the window
			SDL_ShowCursor(0);
			SDL_GetWindowSize(gwindow, &MAX_WIDTH, &MAX_HEIGHT);   //Get the window dimensions
				if (gwindow != NULL)
			{
				grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_Surface* icon_surface = IMG_Load("player.png");   //Set the window icon
				SDL_SetWindowIcon(gwindow, icon_surface);
				if (grenderer != NULL)
					return true;
				else
					return false;
			}
			else
				return false;


		}
		else
			return false;
	}
	else
		return false;

}


//This function converts its input to its corresponding binary string
string binary(int number) {  
	string result;
	if (!full_screen)
	      result = bitset<6>(number).to_string();
	else
	     result = bitset<9>(number).to_string();

	return result;
}

//Generate the binary strings of first n numbers
void fillpattern()
{
	for (int i = 0; i < pow(2,glane_no) * 2; i++)
	{
		pattern.push_back(binary(i));
	}
}

//Load the fonts for rendering
void loadfont()
{
	gfont = TTF_OpenFont("Assets/fonts/score.otf", 28);
	score_font = TTF_OpenFont("Assets/fonts/score.otf", 28);
	
	gcolor = { 0xff, 0xff, 0xff, 0xff };
}

//This function displays the mainmenu
void mainmenucheck()
{
	//Reset all the mainmenu variables
	mainmenu.reset();
	//Loop till the user has made a choice
	while ((inMenu))
	{
		if (SDL_PollEvent(&e) != 0)

		{
			switch (e.type)
			{
			case SDLK_f:
				SDL_SetWindowFullscreen(gwindow, 0);
				full_screen = true;
				glane_no = 9;
				fillpattern();
				SDL_GetWindowSize(gwindow, &MAX_WIDTH, &MAX_HEIGHT);
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			
				mainmenu.handleEvent(e);
				break;
			
			case SDL_QUIT:

				close();
				break;
			

			}
		}

		switch (mainmenu.getSelection())
		{

		case PLAY_GAME: inMenu = false;
			gameover_menu = false;
			player.reset(100, 50);
			playgame();
			break;

		case STATS:
			statdisplay();
			
			break;
		case QUIT_GAME:
			quit = true;
			inMenu = false;
			close();
			break;
		}


		SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
		//Render the scrolling background
		background.render(0, background.getScroll());
		background.render(0, (background.getScroll() - background.getHeight()));
		//Render the mainmenu
		mainmenu.render();
		SDL_RenderPresent(grenderer);

	}
}
//This function handles the high score display option
void statdisplay()
{

	statDisplay.reset();
	statDisplay.loadfont(score_font, gblue);
	while (statDisplay.getSelection() <= 0)
	{
		
		statDisplay.handleEvent(e);
		SDL_RenderClear(grenderer);
		SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);

		background.render(0, background.getScroll());
		background.render(0, (background.getScroll() - background.getHeight()));
		statDisplay.render();
		SDL_RenderPresent(grenderer);


	}

	if (statDisplay.getSelection() == 2)
	{
		quit = true;
		inMenu = false;
		close();
	}
	else
	{
		gameover_menu = false;
		mainmenucheck();

	}
}
//The following function is the main game loop.
void playgame()
{
	
	//Reset the power ups
	powerUp_ammo.reset();
	
	
	

//Iniitialize the ammo count
	ammo_count = 100;
	time_count = 0; //The timer for the score
	background.setSpeed(1);  //Set the scrolling speed of the background
	player.setWindowDimension(MAX_WIDTH, MAX_HEIGHT);
	player.reset(100, 50);  //Initial health and shield
	//Set the parameters for the explosion effect
	hit_effect.setRenderer(grenderer);
	hit_effect.loadimage("explosion0.png");

	//The parameters for the pause screen. I have implemented a very basic version of a pause screen: Just display the word PAUSE and stop all the moving elements of the game
	pause_effect.setRenderer(grenderer);
	pause_effect.loadfont(score_font,gblue);

	//The following resets the timers. This is done so that the timer starts again if the player plays the game again after a game over.
	if (speed_timer.isStarted())
	{
		speed_timer.stop();
	}
	if (score_timer.isStarted())
	{
		score_timer.stop();
	}
	if (blink_timer.isStarted())
	{
		blink_timer.stop();
	}

	powerUp_ammo.setRenderer(grenderer);
	for (int k = 0; k < 2; k++)
	{
		for (int j = 0; j < glane_no; j++)
		{
			asteroid_group[k][j].reset();

			

		}
	}
	for (int k = 0; k < 2; k++)
	{
		for (int j = 0; j < glane_no; j++)
		{
			asteroid_group[k][j].setRenderer(grenderer);

			asteroid_group[k][j].loadimage("a10000.png");


		}
	}
	background.setSpeed(2);
	speed_timer.start();
	score_timer.start(); 
	blink_timer.start();
	Timer hit_timer;
	final_score = 0;
	hit_points = 0;
	bool PAUSED = false;
	int POWER_UP_TYPE = 0;
	int bg_vel = 2;
	SDL_RenderClear(grenderer);
	//Lopp till the player survives or doesnt quit
	while (!quit && player.getHealth() > 0)
	{

		//Seed for random number
		srand(time(0));
	

		if (SDL_PollEvent(&e) != 0)

		{

			switch (e.type)
			{
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					//Fire if the player has pressed SPACE. The Bullet's positions are determined based on the player's position
					temp_bullet.setPosition(player.getX() + 35, player.getY());
					//A vector is used to store all the bullets shot
					bullets.push_back(temp_bullet);
					//Play the audio if the mute flag is not set and there are bullets left
					if (!isMute && ammo_count > 0)
					{
						audio_manager.playEffect("shoot", 0);
					}
					if (ammo_count > 0)
					{

						ammo_count--;
					}
					else
						ammo_count = 0;
					break;

				}
				else if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					PAUSED = !PAUSED;
				}
				else if (e.key.keysym.sym == SDLK_m)
				{
					isMute = !isMute;
				}
				else
				{
					player.HandleEvent(e);
					break;
				}
			case SDL_KEYUP:
				//if any other key other than space was pressed ( like the directional keys or the WASD then let the Player class handle the event.
				if (e.key.keysym.sym != SDLK_SPACE)
				{
					player.HandleEvent(e);
					break;
				}
				else
				{
					fired = true;
					break;

				}

			case SDL_QUIT:

				quit = true;
				close();
				break;
			}
		}
		else
		{
			
			//Render the player and update his position
			//player.move();
			player.render();
		}


		if (!PAUSED)
		{
			//Move all the game elements (like the asteroids, powerups and the player and the bullets)
			player.move();

			powerUp_ammo.move();

			for (int i = 0; i < bullets.size(); i++)
			{
				if (bullets[i].getRenderFlag())
				{
					bullets[i].move();
				}
				else
					bullets[i].reset();
			}

			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < glane_no; j++)
				{
					asteroid_group[k][j].move();
					//If the asteroid has passed the screen, free the player's lock flag to move
					if (asteroid_group[k][j].getY() > player.getY())
					{
						player.setLockFlag(false);
					}

				}
			}

		}
		//If the power up has crossed the screen or it has not reached the screen
		if (powerUp_ammo.getY() > MAX_HEIGHT || powerUp_ammo.getY() == 0)
		{
			//Generate a random number between 0 and 2. For each number, create a corresponding powerup.
			switch (rand() % 3)
			{
			case 0:
				powerUp_ammo.loadimage("pill_red.png");
				POWER_UP_TYPE = 0;
				break;
			case 1:
				powerUp_ammo.loadimage("pill_blue.png");
				POWER_UP_TYPE = 1;
				break;

			case 2:
				powerUp_ammo.loadimage("pill_green.png");
				POWER_UP_TYPE = 2;
				break;
			}
		}
		//If the Asteroid has crossed the screen, then clear its HIT flag ( because teh Player obviously has not shot it)
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < glane_no; j++)
			{

				if (asteroid_group[k][j].getY() > MAX_HEIGHT)
				{
					asteroid_group[k][j].setHit(false);

				}

			}
		}

		if (powerUp_ammo.getY() > MAX_HEIGHT)
		{
			powerUp_ammo.setHit(false);

		}
		//This is the random generation algorithm
		for (int k = 0; k < 2; k++)
		{
			int posx = 0, posy;
			//Create a string of binary digits. The power function is  used to determine the maximum range. For example, if there were three lanes, then we would need 2^3 i.e 8 variables.
			char* patt = (char*)pattern[rand() % (int)(pow(2, glane_no))].c_str();
			
			

			for (int j = 0; j < glane_no; j++)
			{

				//Always leave a gap of double the player's size between the rows of the  asteroids
				posy = -(player.getHeight() * 2);


				if (asteroid_group[k][j].getY() > MAX_HEIGHT)
				{

					asteroid_group[k][j].setHit(false);


					//Create the asteroid if the binary digit is 1
				
					if (patt[j] == '1')
					{

						asteroid_group[k][j].setRenderFlag(true);
						asteroid_group[k][j].setPosition(posx, posy);
						//Increase the X position for the next asteroid
						posx += asteroid_group[k][j].getWidth();
						//Make sure the asteroid doesnt render at the point farther than the screen width
						if (posx + asteroid_group[k][j].getWidth() > (MAX_WIDTH))
						{
							posx = MAX_WIDTH - asteroid_group[k][j].getWidth();
						}

					}
					else
					{
						
						//If the number is not 1, increment the X position and set the render flag to false
						posx += asteroid_group[k][j].getWidth();
						asteroid_group[k][j].setRenderFlag(false);
						if (posx + asteroid_group[k][j].getWidth() > (MAX_WIDTH))
						{
							posx = MAX_WIDTH - asteroid_group[k][j].getWidth();
						}

					}



				}

			}

		}
		
		if (powerUp_ammo.getY() > MAX_HEIGHT)
		{
			//Generate a random number between 0 and 1. If it is 1, render the poweup else do not. Note that the type of pwerup is also randomly generated.
			if (rand() % 2)
			{

				powerUp_ammo.setPosition(rand() % (MAX_WIDTH - powerUp_ammo.getWidth()), -50);
				powerUp_ammo.setRenderFlag(true);
			}
			else
				powerUp_ammo.setRenderFlag(false);
		}
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < glane_no; j++)
			{
				//Check if the asteroid and the player collide. It has to be checked tht the Asteroid has its render flag set and HIT flag cleared ( which means the asteroid is present on the screen and has not been shot at )
				if (collider.checkCollision(player.getCollider(), asteroid_group[k][j].getCollider()) && asteroid_group[k][j].getRenderFlag() && !asteroid_group[k][j].getHit())
				{
					player.isHit();
				}






			}

		}

		//Check the collision between the player and the powerup rendererd
		if (collider.checkCollision(player.getCollider(), powerUp_ammo.getCollider()) && powerUp_ammo.getRenderFlag())
		{
			//If collided, stop rendering it
			powerUp_ammo.setRenderFlag(false);
			switch (POWER_UP_TYPE)
			{

				//Increase the attribute according to the type of powerup
			case 0:
				if (player.getHealth() <= 80)
				{
					player.setHealth(player.getHealth() + 20);
				}
				else
					player.setHealth(100);
				break;
			case 1:
				if (player.getShield() <= 30)
				{
					player.setShield(player.getShield() + 20);

				}
				else

					player.setShield(50);

				break;
			case 2:
				if (ammo_count <= 80)
				{
					ammo_count += 20;
				}
				else
				{
					ammo_count = 100;
				}
				break;
			}
		}
	

		//Now check for collison between the bullets and the asteroid
		for (int l = 0; l < bullets.size(); l++)
		{
			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < glane_no; j++)
				{
					if (collider.checkCollision(bullets[l].getCollider(), asteroid_group[k][j].getCollider()) && asteroid_group[k][j].getRenderFlag() && !asteroid_group[k][j].getHit() && ammo_count > 0)
					{
						//If collided, display the explosion
						hit_effect.setPosition(asteroid_group[k][j].getX(), asteroid_group[k][j].getY());
						//Set the HIT flag of the asteroid
						asteroid_group[k][j].setHit(true);
						//Dont display the bullet
						bullets[l].setRenderFlag(false);
						bullets[l].setHit(true);
						//Increase the score of the player by 20
						hit_points += 20;
						//Play the sound if unmuted
						if (!isMute)
						{
							audio_manager.playEffect("explosion", 0);
						}
						//Start the timer for the explosion effect
						hit_timer.start();



					}


				}

			}
		}

		//The score is calculated as a sum of the asteroids hit and the time the player survives. If the game is paused, we stop the speed timer
		if (PAUSED)
		{
			if (speed_timer.isStarted())
				speed_timer.pause();
		}
		else
			if (speed_timer.isPaused())
				speed_timer.resume();

		SDL_RenderFillRect(grenderer, &stat_rect);

		//Render the background consecutively to achieve a scrolling effect
		background.render(0, background.getScroll());

		background.render(0, (background.getScroll() - background.getHeight()));

		if (PAUSED)
		{
		//if the game is paused, freeze the background
			background.setSpeed(0);
		}
		else
		{
			background.setSpeed(2);
		}
			

//Render the asteroids
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < glane_no; j++)
			{
				if (asteroid_group[k][j].getRenderFlag())
				{
					asteroid_group[k][j].render();
				}


			}
		}
		//Render the powerups
		if (powerUp_ammo.getRenderFlag())
		{
			powerUp_ammo.render();
		}
		//Display the explosion effect for the time specified
		if (hit_timer.isStarted() && hit_timer.getTicks() < 10)
		{
			
				hit_effect.loadimage("explosion1.png");
				hit_effect.render();
			
			
			
			hit_timer.stop();
		}
		//Render the player
		player.render();
		//If the game is paused, display the PAUSED and freeze all the elements
		if (PAUSED)
		{
			pause_effect.loadtext("PAUSED");
			pause_effect.setDimension(MAX_WIDTH, (MAX_HEIGHT / 4));
			pause_effect.setPosition(0,(MAX_HEIGHT/2 - (MAX_HEIGHT / 4)));
			pause_effect.render();
		}
			
			
		//Render the bullets only if the ammo exists
		for (int i = 0; i < bullets.size(); i++)
		{
			if (ammo_count > 0)
			{

  				bullets[i].render();
			}
		}
		//Update the score
		if (!PAUSED)
		{
			final_score = score_timer.getTicks() + hit_points;
		}
		
		//A string stream is used as it is easy to populate it
		stringstream score;
		score << "SCORE : " << final_score;
		stringstream missile;
		//If the ammo is 0, display in a blinking text that the player is OUT OF AMMO
		if (ammo_count == 0)
		{
			//The transparency is reset every second
			if (blink_timer.getTicks() > 1)
			{
				
				

					blink_timer.stop();
					missile_updater.setAlpha(0);
					missile << "OUT OF AMMO";

				

			}
			else
			{

				missile_updater.setAlpha(255);
				missile << "OUT OF AMMO";


			}


		}
		else
		//If there is ammo, display the bullet count
		{
			missile << "AMMO :" << ammo_count;
		}
		//Render the score
		score_updater.render(MAX_WIDTH - 200, MAX_HEIGHT - 100, score.str());
		//Render the missile count
		missile_updater.render(10, MAX_HEIGHT - 100, missile.str());
		SDL_RenderPresent(grenderer);
		time_count++;
		//For every 15 seconds, increase the speed of the asteroids
		if (speed_timer.getTicks() > 15)
		{
			speed_timer.stop();
			
			for (int k = 0; k < 2; k++)
			{
				for (int j = 0; j < glane_no; j++)
				{
					if (asteroid_group[k][j].getRenderFlag())

						asteroid_group[k][j].setVelocity(asteroid_group[k][j].getVelocity() + 2);

				}
			}
		}
		//Stop the timer if it is started
		if (!speed_timer.isStarted())
			speed_timer.start();
		if (!blink_timer.isStarted())
		{
			blink_timer.start();
		}



	
}
//If the player dies, go to the game over menu
if (player.getHealth() == 0)
{
	gameover_menu = true;
	game_over();
}
//If the player quits
if (quit)
{
	SDL_Quit();
	exit(0);
}
}
//The GAME OVER MENU
void game_over()
{
	//Reset the menu
	gameover.reset();
	
	
	//As long as the player is in the game over menu, repeat the loop
	while ((gameover_menu))
	{
		if (SDL_PollEvent(&e) != 0)

		{
			switch (e.type)
			{
			//Player presses the arrow kets, let the Gameover class handle the event
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				gameover.handleEvent(e);
				break;
			case SDL_QUIT:

				
				close();
				break;
			}
		}
		//Get the selection and process it
		switch (gameover.getSelection())
		{
		case REPLAY_GAME:
			playgame();
			break;
		case SAVE_SCORE:
			//If save score, then go to the save game menu
			savegamedata();
			
			
			break;
		case MAIN_MENU:
			inMenu = true;
			mainmenucheck();
			break;
		}
		//Render the data
		SDL_RenderClear(grenderer);
		SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);

		background.render(0, background.getScroll());
		background.render(0, (background.getScroll() - background.getHeight()));
		gameover.setScore(final_score);
		gameover.render();
		SDL_RenderPresent(grenderer);

	}
}
//The SAVE GAME MENU
void savegamedata()
{
	background.setSpeed(2);
	save_menu.reset();
	//Open the Text Input
	SDL_StartTextInput();
	//Repeat as long as the player has not pressed return
	while (save_menu.getSelection() != 1)
	{
		
		save_menu.handleEvent(e);
		SDL_SetRenderDrawColor(grenderer, 0xff, 0xff, 0xff, 0xff);
		//Render the background and the score
		background.render(0, background.getScroll());
		background.render(0, (background.getScroll() - background.getHeight()));
		save_menu.setScore(final_score);
		save_menu.render();
		SDL_RenderPresent(grenderer);
		

	}
	SDL_StopTextInput();
	inMenu = true;
	//Return to the mainmenu
	mainmenucheck();
}
int main(int argc, char** argv)
{

	//Initialize the systems and load the renderers for all the elements
	if (init())
	{
		temp_bullet.setRenderer(grenderer);
		temp_bullet.loadimage("laserGreen.png");
		player.setRenderer(grenderer);
		player.loadimage("player.png");
		
		
		background.setRenderer(grenderer);
		background.setDimension(MAX_WIDTH, MAX_HEIGHT);

		background.loadimage("background.png");
		mainmenu.setRenderer(grenderer);
		gameover.setRenderer(grenderer);
		statDisplay.setRenderer(grenderer);
		statDisplay.setDimension(MAX_WIDTH, MAX_HEIGHT);

		score_updater.setRenderer(grenderer);

		missile_updater.setRenderer(grenderer);

		//Generate all the digits
		fillpattern();
		//Open all the fonts
		loadfont();
		mainmenu.loadfont(gfont, gcolor);
		gameover.loadfont(score_font, gblue);
		statDisplay.loadfont(score_font, gblue);
		save_menu.setRenderer(grenderer);
		save_menu.loadfont(score_font, gblue);

		missile_updater.loadFont(score_font, gcolor);
		score_updater.loadFont(score_font, gcolor);

		while (!quit)
		{
			mainmenu.reset();
			mainmenucheck();
			
		}
		close();
		return 0;
	}
}
void close()
{
	//Destroy all the class objects and textures
	SDL_DestroyTexture(gtexture);
	SDL_DestroyRenderer(grenderer);
	player.destroy();
	mainmenu.destroy();
	gameover.destroy();
	statDisplay.destroy();
	save_menu.destroy();
	background.destroy();
	hit_effect.destroy();
	pause_effect.destroy();
	powerUp_ammo.destroy();
	powerUp_health.destroy();
	powerUp_shield.destroy();
	for (int k = 0; k < 2; k++)
	{
		for (int j = 0; j < glane_no; j++)
		{
			
			
			asteroid_group[k][j].destroy();
			


		}
	}
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	exit(0);
	
}

int getRandomNumber()
{
	return rand() % 4;
}



