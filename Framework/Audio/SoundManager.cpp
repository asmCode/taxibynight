#include "SoundManager.h"
#include <stdio.h>
#include <assert.h>
#include <Utils/Log.h>

#include "AudioPlayerFactory.h"

const std::string SoundManager::SoundFiles[] =
{
	std::string("button.mp3")
};

SoundManager::SoundManager()
{
	soundVolume = 0.5f;
	musicVolume = 0.5f;
	
	music = NULL;
	
	memset(sounds, 0, sizeof(IAudioPlayer*) * SoundsCount);
}

SoundManager::~SoundManager()
{
}

bool SoundManager::Initialize(const std::string &audioPath)
{
	music = AudioPlayerFactory::CreateAqAudioPlayer(audioPath + "music01.mp3");
	music->SetLoop(true);
	music->SetVolume(musicVolume);
	
	for (unsigned i = 0; i < SoundsCount; i++)
	{
		Log::LogT("loading: %s", SoundFiles[i].c_str());
		sounds[i] = AudioPlayerFactory::CreateAlAudioPlayer(audioPath + SoundFiles[i], false);
		sounds[i]->SetVolume(soundVolume);
	}
	
	return true;
}

void SoundManager::SetSoundVolume(float value)
{
	this->soundVolume = value;
	
	for (unsigned i = 0; i < SoundsCount; i++)
		sounds[i]->SetVolume(value);
}

void SoundManager::SetMusicVolume(float value)
{
	this->musicVolume = value;
	
	music->SetVolume(value);
}

float SoundManager::GetSoundVolume() const
{
	return soundVolume;
}

float SoundManager::GetMusicVolume() const
{
	return musicVolume;
}

void SoundManager::PlayMusic()
{
	//return;
	
	assert(music != NULL);
	music->Play();
}

void SoundManager::StopMusic()
{
	music->Stop();
}

void SoundManager::PlaySound(SoundManager::Sound sound)
{
	sounds[sound]->Play();
}
