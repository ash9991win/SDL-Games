#include"Bullet.h"

Bullet::Bullet()
{
	mPosx = 0;
	mPosy = 0;
	mVelx = 0;
	mVely = 0;
	mdamage = 0;
	mobjecttexture = 0;

}





//Change the Y coordinate
void Bullet::move()
{
	//Since the bullet moves up, the Y coordinate is decreased by the velocity of the bullet.
	mPosy -= BULLET_VEL;
	//Update the collider of the bullet
		collider.x = mPosx;
		collider.y = mPosy;
		collider.w = 4;
		collider.h = 30;
	
	
		
}


void Bullet::reset()
{
	mPosx = 0;
	mPosy = 0;
	mVelx = 0;
	mVely = 0;
	collider = { 0, 0, 0, 0 };

}



//Draw onto the screen
void Bullet::render()
{
	SDL_Rect coord;



	SDL_SetRenderDrawColor(current_renderer, 0xFF, 0xFF, 0xFF, 0xff);
	//Draw the bullet only if the render flag is set and the HIT flag is not. If the render flag is set, it means the player has pressed space. If the HIT flag is set, it meaans the bullet has struck an asteroid.
	if (render_flag && !isHit)
	{
		//Reset the collider

		collider = { 0, 0, 0, 0 };

		coord.x = mPosx + 10;
		coord.y = mPosy;
		coord.w = 5;
		coord.h = 40;
		SDL_RenderCopy(current_renderer, mobjecttexture, NULL, &coord);

	}
	
}



void Bullet::setRenderFlag(bool flag)
{
	render_flag = flag;
}

bool Bullet::getRenderFlag()
{
	return render_flag;
}




void Bullet::setHit(bool value)
{
	isHit = value;
}