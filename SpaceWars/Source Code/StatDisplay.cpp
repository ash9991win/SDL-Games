#include"StatDisplay.h"
#include<iostream>
//The leaderboard
void StatDisplay::handleEvent(SDL_Event& e)
{

	while (SDL_PollEvent(&e) != 0)
	{

	
		 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE)
		{

			///If the player presses backspace, return to the mainmenu
			finalselection = 1;
		}
		 else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c)
		 {
			 file_handler.clear();
		 }
		else if (e.type == SDL_QUIT)
		 {
			finalselection = 2;
		 }
	}
}

void StatDisplay::loadfont(TTF_Font* font, SDL_Color color)
{
	this->font = font;
	this->color = color;
	//Load the texts 
	title_texture = itemloader.loadtext(currentrenderer, font, color, "NAME                            SCORE");
	temp_texture = 0;
	texture_data.clear();
	score_texture.clear();




	menu_item3 = itemloader.loadtext(currentrenderer, font, color, "PRESS BACKSPACE FOR MAIN MENU");
	texture_data = file_handler.read();
	//load the textures according to the file data
	for (int i=0; i< texture_data.size(); i++)
	{
		stringstream temp_stream;
		temp_stream << texture_data[i].first << "                             " << texture_data[i].second;
		temp_texture = itemloader.loadtext(currentrenderer, font, color, temp_stream.str());
		score_texture.push_back(temp_texture);
	}
	
}
//Draw onto the screen
void StatDisplay::render()
{
	title_rect.x = 10;
	title_rect.y = 10;
	title_rect.h = 90;
	title_rect.w = maxwidth;

	stat_rect = new SDL_Rect[score_texture.size()];
	SDL_RenderCopy(currentrenderer, title_texture, NULL, &title_rect);
	
	for (int i = 0; i < score_texture.size(); i++)
	{
		if (i < 7)
		{


			stat_rect[i].x = 10;
			stat_rect[i].y = (i + 1) * 80;
			stat_rect[i].w = maxwidth - 20;
			stat_rect[i].h = 30;

			SDL_RenderCopy(currentrenderer, score_texture[i], NULL, &stat_rect[i]);
		}

		

 	}

	

	destrect[0].x = 10;
	destrect[0].y = (maxheight - 30);
	destrect[0].h = 20;
	destrect[0].w = 500;


	SDL_RenderCopy(currentrenderer, menu_item3, NULL, &destrect[0]);

}

void StatDisplay::setDimension(int w, int h)
{
	maxwidth = w;
	maxheight = h;
}