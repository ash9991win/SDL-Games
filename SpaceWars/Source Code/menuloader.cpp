#include"menuloader.h"

Mainmenu::Mainmenu(){

	current_selection = 1;
	finalselection = 0;
	destrect = new SDL_Rect[3];
	menu_item1 = menu_item2 = menu_item3 = title_texture=0;
}
//Reset all the selections
void Mainmenu::reset()
{
	current_selection = 1;
	finalselection = 0;
}

int Mainmenu::getSelection()
{
	return finalselection;
}
//Whenever a player presses the down arrow, increase the current_selection and decrease it if the player presses the up arrow
//If the player presses enter, then that is the final selection
void Mainmenu::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_s:
		case SDLK_DOWN: if (current_selection == 3)
			current_selection = 1;
						else
							current_selection += 1;
			break;
		case SDLK_w:
		case SDLK_UP: if (current_selection == 1)
			current_selection = 3;
					  else current_selection -= 1;
					  break;

		case SDLK_RETURN:
			finalselection = current_selection;
		}
	}
}


void Mainmenu::setRenderer(SDL_Renderer* prenderer)
{
	currentrenderer = prenderer;
}

//Draw the menu items. The one with the current selection has its width twice that of the others.
void Mainmenu::render()
{
	title_rect.x = 100;
	title_rect.y = 10;
	title_rect.h = 90;
	title_rect.w = 500;
	for (int i = 0; i < 3; i++)
	{

		if ((i + 1) == current_selection)
		{
			destrect[i].x = 200 ;
			destrect[i].y = 150 * (i + 1);
			destrect[i].w = 300;
			destrect[i].h = 80;
		}
		else
		{
			destrect[i].x = 200 ;
			destrect[i].y = 150 * (i + 1);
			destrect[i].w = 200;
			destrect[i].h = 80;
		}
		}

	SDL_RenderCopy(currentrenderer, title_texture, NULL, &title_rect);

	SDL_RenderCopy(currentrenderer, menu_item1, NULL, &destrect[0]);

	SDL_RenderCopy(currentrenderer, menu_item2, NULL, &destrect[1]);

	SDL_RenderCopy(currentrenderer, menu_item3, NULL, &destrect[2]);

}

void Mainmenu::loadfont(TTF_Font* font, SDL_Color color)
{
	title_texture = itemloader.loadtext(currentrenderer, font, color, "GALAXY!");

	menu_item1 = itemloader.loadtext(currentrenderer, font, color, "PLAY GAME");
	menu_item2 = itemloader.loadtext(currentrenderer, font, color, "HIGH SCORES");
	menu_item3 = itemloader.loadtext(currentrenderer, font, color, "QUIT GAME");

}

void Mainmenu::destroy()
{
	itemloader.destroy();
	
	SDL_DestroyTexture(title_texture);
	title_texture = NULL;
	SDL_DestroyTexture(menu_item1);
	menu_item1 = NULL;
	SDL_DestroyTexture(menu_item2);
	menu_item2 = NULL;
	SDL_DestroyTexture(menu_item3);
	menu_item3 = NULL;
	SDL_DestroyRenderer(currentrenderer);
}