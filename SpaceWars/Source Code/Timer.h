/**
SPACE WARS
This is a timer class. It is used to calculate various timing processses. In the current version, it is used to calculate the score and also as an animation timer
*/#ifndef TIMER_H
#define TIMER_H
#include<SDL.h>
class Timer
{
public:
	/**
	A constructor to initialize the variables
	*/
	Timer();
	/**
	Start the timer
	*/
	void start();
	/**
	Pause the timer
	*/
	void pause();
	/**
	Stop a running timer
	*/
	void stop();
	/**
	Resume a paused timer
	*/
	void resume();
	/**
	Return the number of seconds elapsed
	Return Values: the number of seconds elapsed
	*/
	int getTicks();
	/**
	Check if timer is running
	Return Values: TRUE if the timer is running, flase otherwise
	*/
	bool isStarted();
	/**
	Check if the timer is paused
	Return Values: TRUE if paused, false otherwise
	*/
	bool isPaused();

private:
	/**
	The number of ticks from the start of timer
	*/
	Uint32 mstart_ticks;
	/**
	The number of ticks after pausing the timer
	*/
	Uint32 mpause_ticks;
	/**
	The PAUSED and STARTED flags
	*/
	bool mpaused, mstarted;

};
#endif