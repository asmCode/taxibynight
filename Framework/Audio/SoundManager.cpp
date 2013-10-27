#include "SoundManager.h"
#include <stdio.h>
#include <assert.h>
#include <Utils/Log.h>
#include <memory.h>

#include "AudioPlayerFactory.h"

SoundManager *SoundManager::m_instance;

const std::string SoundManager::SoundFiles[] =
{
	std::string("button.mp3")
	//std::string("SampleMP3.mp3")
	//std::string("a.mp3")
	//std::string("engine.mp3")
};

SoundManager *SoundManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new SoundManager();

	return m_instance;
}

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
	music = AudioPlayerFactory::CreateTizenAudioPlayer(audioPath + "SampleMP3.mp3");
	music->SetLoop(true);
	music->SetVolume(musicVolume);
	
	m_engine = AudioPlayerFactory::CreateAlAudioPlayer(audioPath + "engine.mp3", false);
	m_engine->SetLoop(true);
	m_engine->SetVolume(soundVolume);

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

void SoundManager::StartEngine()
{
	m_engine->Play();
}

void SoundManager::StopEngine()
{
	m_engine->Stop();
}

void SoundManager::SetEnginePitch(float pitch)
{
	m_engine->SetPitch(pitch);
}
