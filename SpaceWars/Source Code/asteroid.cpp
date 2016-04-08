#include"asteroid.h"
//Initialize the variables
Space::Space()
{
	mPosx = mPosy = mwidth = mheight = 0;
	currentrenderer = 0;
	rotate = 0;
	mobjecttexture = 0;
	isHit = false;
}
//Reset all the variables
void Space::reset()
{
	mPosx = mPosy = mwidth = mheight = 0;
	currentrenderer = 0;
	rotate = 0;
	mobjecttexture = 0;
	isHit = false;
	velocity = 4;
}
//Set the position of the object
void Space::setPosition(int x, int y)
{
	mPosx = x;
	mPosy = y;

}
//Set the reenderer

void Space::setRenderer(SDL_Renderer* prenderer)
{
	currentrenderer = prenderer;
}
//Set the hit flag
void Space::setHit(bool hit)
{
	isHit = hit;
}
//Return the hit flag
bool Space::getHit()
{
	return isHit;
}
//Draw onto the screen
void Space::render()
{
	SDL_Rect dest;
	
	

	

	dest.x = mPosx;
	dest.y = mPosy;
	dest.w = mwidth;
	dest.h = mheight;
	//Only if the RENDER flag is set and the HIT flag is not set, we have to draw. If the HIT flag is set, it means the player has shot down the asteroid, so we shouldnt render it
	if (ifrender && !isHit)
	{


		SDL_RenderCopyEx(currentrenderer, mobjecttexture, NULL, &dest, rotate, NULL, SDL_FLIP_NONE);
	}
	//Since an else means the HIT flag is set, we have to reset the collider
	else
	{

		collider = { 0, 0, 0, 0 };

	}
}
bool Space::istexture()
{
	return texture_present;
}


//Move the object
void Space::move()
{
	//Rotate it incrementally
	rotate += 5;
	//The collider should match the position of the asteroid/object
	collider.x = mPosx + 5;
	collider.y = mPosy;
	collider.w = mwidth - 10;
	collider.h = mheight - 15;
	//Increase the Y coordinate by the speed of the object
	mPosy += velocity;
	

}


int Space::getX()
{
	return mPosx;
}

int Space::getY()
{
	return mPosy;
}

int Space::getHeight()
{
	return mheight;
}
int Space::getWidth()
{
	return mwidth;
}

void Space::loadimage(string filename)
{
	mobjecttexture = mobjectloader.loadimage(currentrenderer, filename);
	mwidth = mobjectloader.getWidth();
	mheight = mobjectloader.getHeight();

	
}

SDL_Rect Space::getCollider()
{
	return collider;
}

bool Space::getRenderFlag()
{
	return ifrender;
}

void Space::setRenderFlag(bool flag)
{
	ifrender = flag;
}

int Space::getVelocity()
{
	return velocity;
}

void Space::setVelocity(int new_velocity)
{
	velocity = new_velocity;
}
void Space::destroy()
{
	mobjectloader.destroy();
	SDL_DestroyTexture(mobjecttexture);
	SDL_DestroyRenderer(currentrenderer);
}