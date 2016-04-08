/**
SPACE WARS 
AudioManager.h
The following class handles the sound effects

Author: Ashwin Sankaranarayanan
*/
#ifndef AUDIO_H
#define AUDIO_H
#include<SDL.h>
#include<SDL_mixer.h>
#include<map>
using namespace std;
const int PLAYING = 1;
const int PAUSED = 2;
class AudioManager
{
public:
	/**
	The constructor for initializing
	*/
	AudioManager();
	/**
	Plays a given effect.
	Parameters: The file name and the count for repeating the effect.
	*/
	void playEffect(string name, int repeat);
	/**
	
	/**
	Destructor 
	*/
	~AudioManager();
private:
	map<string, Mix_Chunk*> audio_loader;   //This is the map for the resource. It's keys are strings and its values are Mix_Chunk which is the SDL datatype for audio files.


};
#endif
