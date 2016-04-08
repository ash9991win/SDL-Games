#include"SaveData.h"

void SaveData::handleEvent(SDL_Event &e)
{
	
	while (SDL_PollEvent(&e) != 0)
	{

		if (e.type == SDL_KEYDOWN && e.key.keysym.sym != SDLK_RETURN)
		{
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
			{
				//Discard character
				inputText.pop_back();
				renderText = true;
			}
			//Handle if the player copies
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(inputText.c_str());
			}
			//Handle if the player pastes
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				inputText = SDL_GetClipboardText();
				renderText = true;
			}

			
		}
		else if (e.type == SDL_TEXTINPUT)
		{
			//Not copy or pasting
			if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
			{
				//Append character
				inputText += e.text.text;
				renderText = true;
			}
		}
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
		{ 
			//If the player presses return, then write onto the file ( only if the name is not empty).Set the final selection variable to 1
			if (inputText != " " ||  !inputText.empty())
				
			file_handler.write(inputText, score);
		
			finalselection = 1;
		}
	}
}

void SaveData::setScore(int score)
{
	this->score = score;
}
void SaveData::loadfont(TTF_Font* font, SDL_Color color)
{
	this->font = font;
	this->color = color;
	title_texture = itemloader.loadtext(currentrenderer, font, color, "ENTER NAME");
	name_texture = itemloader.loadtext(currentrenderer, font, color, inputText);
	
	menu_item3 = itemloader.loadtext(currentrenderer, font, color, "PRESS ENTER FOR MAIN MENU");

}

void SaveData::render()
{
	title_rect.x = 100;
	title_rect.y = 10;
	title_rect.h = 90;
	title_rect.w = 500;
	for (int i = 0; i < 3; i++)
	{

		
			destrect[i].x = 200;
			destrect[i].y = 150 * (i + 1);
			destrect[i].w = 300;
			destrect[i].h = 100;
		
	}

	name_texture = itemloader.loadtext(currentrenderer, font, color, inputText);


	SDL_RenderCopy(currentrenderer, title_texture, NULL, &title_rect);

	SDL_RenderCopy(currentrenderer, name_texture, NULL, &destrect[0]);


	SDL_RenderCopy(currentrenderer, menu_item3, NULL, &destrect[2]);

}
void SaveData::reset()
{
	Mainmenu::reset();
	inputText.clear();
}

void SaveData::destroy()
{
	Mainmenu::destroy();
	SDL_DestroyTexture(name_texture);
}