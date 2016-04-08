#include"Background.h"
//initialize the variables
Background::Background()
{
	background = 0;
	scrolloffset = 0;
	mwidth = 0;
	mheight = 0;
}
//Set the renderer
void Background::setRenderer(SDL_Renderer* prenderer)
{
	current_renderer = prenderer;
}
//Load the texture
void Background::loadimage(string filename)
{
	background = bg_loader.loadimage(current_renderer, filename);
	mwidth = bg_loader.getWidth();
	mheight = bg_loader.getHeight();

}
//Set the Window dimension
void Background::setDimension(int width, int height)
{
	maxwidth = width;
	maxheight = height;
}
//Draw onto the screen
void Background::render(int x, int y)
{
	SDL_Rect quad;
	quad.x = x;
	quad.y = y;
	quad.w = mwidth;
	quad.h = mheight;
	//To create a scrolling background, we render the images one after the another with a gap of the scroll offset. 
	scrolloffset += background_speed;
	if (scrolloffset > mheight)
	{
		scrolloffset = 0;
		
	}
	


	SDL_RenderCopy(current_renderer, background, NULL, &quad);
}

int Background::getHeight()
{
	return mheight;
}

int Background::getWidth()
{
	return mwidth;
}
int Background::getScroll()
{
	return scrolloffset;
}

void Background::setSpeed(int speed)
{
	background_speed = speed;
}

int Background::getSpeed()
{
	return background_speed;
}

void Background::destroy()
{
	bg_loader.destroy();
	SDL_DestroyTexture(background);
	background = NULL;
	SDL_DestroyRenderer(current_renderer);
	current_renderer = NULL;
}