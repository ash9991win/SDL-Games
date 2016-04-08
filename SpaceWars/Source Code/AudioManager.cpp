#include"AudioManager.h"
#include<iostream>
//Initialize the audio system and the variables
AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout<<"SDL_mixer could not initialize! SDL_mixer Error:"<<Mix_GetError();
	}
	Mix_Chunk* temp_chunk;
	temp_chunk = Mix_LoadWAV("Assets/audio/atari_boom.wav");
	audio_loader["explosion"] = temp_chunk;
	temp_chunk = Mix_LoadWAV("Assets/audio/NovaShot.wav");
	audio_loader["shoot"] = temp_chunk;


}

void AudioManager::playEffect(string name, int repeat)
{
	Mix_PlayChannel(-1, audio_loader[name], repeat);
}
AudioManager::~AudioManager()
{
	for (map<string, Mix_Chunk*>::iterator it = audio_loader.begin(); it != audio_loader.end(); it++)
	{
		Mix_FreeChunk(it->second);
		it->second = NULL;
	}

	Mix_Quit();
}