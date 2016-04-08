#include"object.h"
#include<iostream>
using namespace std;
//Load the image
SDL_Texture* Object::loadimage(string filename)
{

	mobjecttexture = mresourceloader.loadimage(current_renderer, filename);
	if (mobjecttexture == NULL)
	{
		cout << IMG_GetError() << " AND " << SDL_GetError() << endl;
	}
	mwidth = mresourceloader.getWidth();
	mheight = mresourceloader.getHeight();
	
	return mobjecttexture;

}
//Update the collider and the x and y coordinates 
void Object::move()
{
	mPosy += mVely;
	mPosx += mVelx;
	collider.x = mPosx;
	collider.y = mPosy;
	collider.w = 4;
	collider.h = 30;


	if (mPosx + mwidth > window_width)
	{
		mPosx -= mVelx;
	}

	if (mPosx  < 0)
	{
		mPosx -= mVelx;
	}


	if (mPosy   < 0)
	{
		mPosy -= mVely;
	}

	if (mPosy + mheight > window_height)
	{
		mPosy -= mVely;
	}
	collider = { mPosx + 5, mPosy + 5, mwidth - 10, mheight - 10 };
}
//Set the window dimensions
void Object::setWindowDimension(int w, int h)
{
	window_width = w;
	window_height = h;
}

void Object::setRenderer(SDL_Renderer* prenderer)
{
	current_renderer = prenderer;
}

int Object::getWidth()
{
	return mwidth;
}
int Object::getHeight()
{
	return mheight;
}

int Object::getX()
{
	return mPosx;
}
int Object::getY()
{
	return mPosy;
}
SDL_Rect Object::getCollider()
{
	return collider;
}
void Object::setPosition(int x, int y)
{
	mPosx = x;
	mPosy = y;
}

void Object::render()
{
		SDL_Rect source;
		SDL_Rect dest;
		dest.x = mPosx;
		dest.y = mPosy;
		dest.w = mresourceloader.getWidth();
		dest.h = mresourceloader.getHeight();
		//Draw the objects onto the screen
		SDL_SetRenderDrawColor(current_renderer, 0xFF, 0xFF, 0xFF, 0xff);	
		SDL_RenderCopyEx(current_renderer, mobjecttexture, NULL, &dest, (double)0, NULL, SDL_FLIP_NONE);

}

int Object::getSpeed()
{
	return speed;
}

void Object::setSpeed(int spx)
{
	speed = spx;
}

void Object::destroy()
{
	SDL_DestroyTexture(mobjecttexture);
	mobjecttexture = NULL;
	SDL_DestroyRenderer(current_renderer);
	current_renderer = NULL;
}