#include"ScoreUpdater.h"

StatUpdater::StatUpdater()
{
	
	current_renderer = 0;
	menu_item2 = 0;
}

void StatUpdater::setRenderer(SDL_Renderer* prenderer)
{
	current_renderer = prenderer;
}

//Draw the string passed onto the screen at the specified position
void StatUpdater::render(int x, int y,string data)
{
	
	menu_item2 = stat_loader.loadtext(current_renderer, font, color, data);
	SDL_SetRenderDrawColor(current_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = 150;
	dest.h = 100;
	//Set the alpha mod according to the alpha variable
	SDL_SetTextureAlphaMod(menu_item2, alpha);
	SDL_RenderCopy(current_renderer, menu_item2, NULL, &dest);
}

void StatUpdater::loadFont(TTF_Font* f, SDL_Color c)
{
	font = f;
	color = c;
	stat_loader.loadtext(current_renderer, f, c, "PLAAAYYY");

}
//Set the transparency
void StatUpdater::setAlpha(int a)
{
	alpha = a;
}
