#include"Timer.h"
Timer::Timer()
{
	mpaused = mstarted = false;
	mpause_ticks = mstart_ticks = 0;
}

//Start the timer
void Timer::start()
{
	mstarted = true;
	mpaused = false;
	mstart_ticks = SDL_GetTicks(); 
	mpause_ticks = 0;
}
//Stop the timer
void Timer::stop()
{
	mstarted = false;
	mpaused = false;
	mstart_ticks = 0;
	mpause_ticks = 0;
}
//Pause the timer
void Timer::pause()
{
	if (mstarted && !mpaused)
	{
		mpaused = true;
		mpause_ticks = SDL_GetTicks() - mstart_ticks;
		mstart_ticks = 0;
	}
}
//Resume the timer
void Timer::resume()
{
	if (mstarted && mpaused)
	{
		mpaused = false;
		mstart_ticks = SDL_GetTicks() - mpause_ticks;
		mpause_ticks = 0;
	}
}
//Get the seconds elapsed
int Timer::getTicks()
{
	Uint32 time = 0;
	if (mstarted)
	{
		if (mpaused)
		{
			time = mpause_ticks;
		}
		else
			time = SDL_GetTicks() - mstart_ticks;

	}
	return (int)(time / 1000);
}

bool Timer::isPaused()
{
	return mpaused;
}

bool Timer::isStarted()
{
	return mstarted;
}