#include"GameOver.h"
#include<sstream>
using namespace std;
Gameover::Gameover() : Mainmenu()
{
	score = 0;
}
//Load the menu items
void Gameover::loadfont(TTF_Font* f, SDL_Color c)
{
	stringstream string_score;
	string_score << "SCORE : " << score;
	font = f;
	color = c;
	title_texture = itemloader.loadtext(currentrenderer, font, color, string_score.str());
	menu_item1 = itemloader.loadtext(currentrenderer, font, color, "RETRY");
	menu_item2 = itemloader.loadtext(currentrenderer, font, color, "SAVE SCORE");
	menu_item3 = itemloader.loadtext(currentrenderer, font, color, "MAIN MENU");
	
}

void Gameover::setScore(int value)
{
	score = value;
}
//Draw onto the screen
void Gameover::render()
{
	title_rect.x = 100;
	title_rect.y = 10;
	title_rect.h = 90;
	title_rect.w = 500;

	stringstream string_score;
	string_score << "SCORE : " << score;
	for (int i = 0; i < 3; i++)
	{

		if ((i + 1) == current_selection)
		{
			destrect[i].x = 200;
			destrect[i].y = 150 * (i + 1);
			destrect[i].w = 200;
			destrect[i].h = 100;
		}
		else
		{
			destrect[i].x = 200;
			destrect[i].y = 150 * (i + 1);
			destrect[i].w = 100;
			destrect[i].h = 100;
		}
	}
	title_texture = itemloader.loadtext(currentrenderer, font, color, string_score.str());

	SDL_RenderCopy(currentrenderer, title_texture, NULL, &title_rect);

	SDL_RenderCopy(currentrenderer, menu_item1, NULL, &destrect[0]);

	SDL_RenderCopy(currentrenderer, menu_item2, NULL, &destrect[1]);

	SDL_RenderCopy(currentrenderer, menu_item3, NULL, &destrect[2]);

}