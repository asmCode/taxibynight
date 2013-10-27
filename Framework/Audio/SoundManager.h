#pragma once

#include <string>
#include "IAudioPlayer.h"

class SoundManager
{
public:
	enum Sound
	{
		Sound_Button = 0,
		
		SoundsCount // always last
	};
	
	static const std::string SoundFiles[];
	
private:	
	static SoundManager *m_instance;

	float soundVolume;
	float musicVolume;
	
	IAudioPlayer *music;
	
	IAudioPlayer *sounds[SoundsCount];
	IAudioPlayer *m_engine;
		
	SoundManager();

public:
	~SoundManager();

	static SoundManager *GetInstance();

	bool Initialize(const std::string &audioPath);
	
	void SetSoundVolume(float value);
	void SetMusicVolume(float value);

	float GetSoundVolume() const;
	float GetMusicVolume() const;
	
	void PlayMusic();
	void StopMusic();
	
	void StartEngine();
	void StopEngine();
	void SetEnginePitch(float pitch);
	
	void PlaySound(Sound sound);
	
	bool IsLoaded() const;
};
