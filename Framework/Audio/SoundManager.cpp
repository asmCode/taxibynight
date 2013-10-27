#include "SoundManager.h"
#include <stdio.h>
#include <assert.h>
#include <Utils/Log.h>
#include <memory.h>

#include "AudioPlayerFactory.h"

SoundManager *SoundManager::m_instance;

const std::string SoundManager::SoundFiles[] =
{
	std::string("collision01.mp3"),
	std::string("collision02.mp3"),
	std::string("collision03.mp3"),
	std::string("button.mp3"),
	std::string("money.mp3"),
	std::string("summary.mp3")
};

SoundManager *SoundManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new SoundManager();

	return m_instance;
}

SoundManager::SoundManager()
{
	soundVolume = 1.0f;
	musicVolume = 1.0f;
	
	music = NULL;
	
	memset(sounds, 0, sizeof(IAudioPlayer*) * SoundsCount);
}

SoundManager::~SoundManager()
{
}

bool SoundManager::Initialize(const std::string &audioPath)
{
#ifndef _WIN32
	music = AudioPlayerFactory::CreateTizenAudioPlayer(audioPath + "city_ambient.mp3");
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
#endif
	
	return true;
}

void SoundManager::SetSoundVolume(float value)
{
	this->soundVolume = value;
	
#ifndef _WIN32
	for (unsigned i = 0; i < SoundsCount; i++)
		sounds[i]->SetVolume(value);
#endif
}

void SoundManager::SetMusicVolume(float value)
{
#ifndef _WIN32
	this->musicVolume = value;
	
	music->SetVolume(value);
#endif
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
#ifndef _WIN32
	//return;
	
	assert(music != NULL);
	music->Play();
#endif
}

void SoundManager::StopMusic()
{
#ifndef _WIN32
	music->Stop();
#endif
}

#undef PlaySoundA
#undef PlaySound

void SoundManager::PlaySound(SoundManager::Sound sound)
{
#ifndef _WIN32
	sounds[sound]->Play();
#endif
}

void SoundManager::StartEngine()
{
#ifndef _WIN32
	m_engine->Play();
#endif
}

void SoundManager::StopEngine()
{
#ifndef _WIN32
	m_engine->Stop();
#endif
}

void SoundManager::SetEnginePitch(float pitch)
{
#ifndef _WIN32
	m_engine->SetPitch(pitch);
#endif
}
