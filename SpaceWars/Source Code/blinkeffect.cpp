#include"blinkeffect.h"
#include<iostream>
using namespace std;
//Set the window dimension
void EffectManager::setDimension(int w, int h)
{
	mwidth = w;
	mheight = h;
}

void EffectManager::setTime(int time)
{
	time_sec = time;
}
//Draw onto the screen
void EffectManager::render()
{
	SDL_Rect dest;
	dest.x = mPosx;
	dest.y = mPosy;
	dest.w = mwidth;
	dest.h = mheight;
	
		SDL_RenderCopy(current_renderer, mobjecttexture, NULL, &dest);

	
}

void EffectManager::loadfont(TTF_Font* font, SDL_Color color)
{
	this->font = font;
	this->color = color;
}

void EffectManager::loadimage(string file)
{
	mobjecttexture = mresourceloader.loadimage(current_renderer, file);
	mwidth = mresourceloader.getWidth();
	mheight = mresourceloader.getHeight();
}

void EffectManager::loadtext(string data)
{
	mobjecttexture = mresourceloader.loadtext(current_renderer, font, color, data);
	mwidth = mresourceloader.getWidth();
	mheight = mresourceloader.getHeight();

}
void EffectManager::start()
{
	effect_timer.start();
	
}
void EffectManager::stop()
{
	effect_timer.stop();
}
void EffectManager::destroy()
{
	SDL_DestroyTexture(mobjecttexture);
	SDL_DestroyRenderer(current_renderer);
}
