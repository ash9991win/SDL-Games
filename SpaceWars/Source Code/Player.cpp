#include"Player.h"
#include<iostream>
#include<vector>
using namespace std;
//initialize the player variables
Player::Player(int health, int shield)
{
	mHealth = health;
	mShield = shield;
	mobjecttexture = 0;
	shield_texture = 0;
	mPosx = window_width / 2;
	mPosy = window_height - mheight - 20;
	
	mwidth = mheight = 0;
	bullet_count = 10;
}
//Reset the player
void Player::reset(int health, int shield)
{
	mHealth = health;
	mShield = shield;
	bullet_count = 10;
	mPosx = window_width / 2 ;
	mPosy = window_height - mheight - 20;
	mVelx = mVely = 0;
	lock_move_flag = false;
}

int Player::getHealth()
{
	return mHealth;
}
int Player::getShield()
{
	return mShield;
}

SDL_Texture* Player::loadimage(string filename)
{
	
	mobjecttexture =  mresourceloader.loadimage(current_renderer, filename);
	mwidth = mresourceloader.getWidth();
	mheight = mresourceloader.getHeight();
	shield_texture = mresourceloader.loadimage(current_renderer, "shield.png");
	


	return mobjecttexture;
}



//Draw the player onto the screen
void Player::render()
{
	SDL_Rect source;
	SDL_Rect dest;
	dest.x = mPosx;
	dest.y = mPosy;
	dest.w = mresourceloader.getWidth();
	dest.h = mresourceloader.getHeight();
	//The health and shield are red and blue rectangles, whose width is equal to the health and the shield values
	
	Hrect.x = mPosx ;
	Hrect.y = mPosy + mresourceloader.getHeight();
	Hrect.h = 10;
	Hrect.w = mHealth;

	Srect.x = mPosx;
	Srect.y = mPosy + mresourceloader.getHeight()  + Hrect.h;
	Srect.h = 10;
	Srect.w = mShield;


	SDL_SetRenderDrawColor(current_renderer, 0xFF, 0x00, 0x00, 0xff);
	SDL_RenderFillRect(current_renderer, &Hrect);

	SDL_SetRenderDrawColor(current_renderer, 0x00, 0x00, 0xFF, 0xff);
	SDL_RenderFillRect(current_renderer, &Srect);

	SDL_SetRenderDrawColor(current_renderer, 0xFF, 0xFF, 0xFF, 0xff);
	//If the shield exists, draw the shield image, else draw the player alone
	if (mShield > 0)
	{
		SDL_Rect shield;
		shield.x = mPosx;
		shield.y = mPosy - 5;
		shield.w = mwidth;
		shield.h = mheight;

			SDL_RenderCopyEx(current_renderer, shield_texture, NULL, &shield, (double)0, NULL, SDL_FLIP_NONE);

	}

	SDL_RenderCopyEx(current_renderer, mobjecttexture, NULL, &dest, (double)0, NULL, SDL_FLIP_NONE);
	

}

void Player::move()
{
	//Only move the player, if the lock flag is not set
	if (!lock_move_flag)
	{
		
		mPosy += mVely;
	}

	mPosx += mVelx;
	if (mPosx + mwidth > window_width)
	{
		mPosx -= mVelx;
	}

	if (mPosx  < 0 )
	{
		mPosx -= mVelx;
	}

	
	if (mPosy   < 0)
	{
		mPosy -= mVely;
	}

	if (mPosy + mheight + 20 > window_height)
	{
		mPosy -= mVely;
	}
	collider = { mPosx + 5, mPosy + 5, mwidth - 10, mheight - 10 };

}

int Player::getBulletCount()
{
	return bullet_count;
}

void Player::HandleEvent(SDL_Event& e)
{
	//Check if the key is pressed and not repeated
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP:
			
				mVely -= PLAYER_VEL;
			
			break;
		case SDLK_s:
		case SDLK_DOWN: mVely += PLAYER_VEL;
			break;
		//If the player moves left or right, display the left and right images
		case SDLK_a:
		case SDLK_LEFT: mVelx -= PLAYER_VEL;
			mobjecttexture = mresourceloader.loadimage(current_renderer, "playerLeft.png");
			break;
		case SDLK_d:
		case SDLK_RIGHT: mVelx += PLAYER_VEL;
			mobjecttexture = mresourceloader.loadimage(current_renderer, "playerRight.png");
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
		case SDLK_UP :
			
				mVely += PLAYER_VEL;
			
			
			
			break;
		case SDLK_s:
		case SDLK_DOWN: 
			mVely -= PLAYER_VEL;
			break;
		case SDLK_a:
		case SDLK_LEFT: 
			mVelx += PLAYER_VEL;
			mobjecttexture = mresourceloader.loadimage(current_renderer, "player.png");
			break;

		case SDLK_d:
		case SDLK_RIGHT: mVelx -= PLAYER_VEL;
			mobjecttexture = mresourceloader.loadimage(current_renderer, "player.png");
			break;
		

		}
	}
	
}

void Player::setLockFlag(bool flag)
{
	lock_move_flag = flag;
}
void Player::isHit()
{
	//If the player is hit, increase the Y position and decrease the shield/health
	mPosy += 5;
	lock_move_flag = true;
	if (mPosy + mwidth > window_height)
	{
		mPosy -= 5;
	}
	if (mShield > 0)
	{
		mShield -= 1;
	}
	
	else if (mHealth > 0)
	{
		mHealth -= 1;
	}
	else
		mHealth = 0;
	

	
	
		
}

bool Player::getLockFlag()
{
	return lock_move_flag;
}

void Player::setHealth(int health)
{
	mHealth = health;
}
void Player::setShield(int shield)
{
	mShield = shield;
}
void Player::destroy()
{
	SDL_DestroyTexture(mobjecttexture);
	mobjecttexture = NULL;
	SDL_DestroyRenderer(current_renderer);
}