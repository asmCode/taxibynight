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
	float soundVolume;
	float musicVolume;
	
	IAudioPlayer *music;
	
	IAudioPlayer *sounds[SoundsCount];
	IAudioPlayer *m_engine;
		
public:
	SoundManager();
	~SoundManager();

	bool Initialize(const std::string &audioPath);
	
	void SetSoundVolume(float value);
	void SetMusicVolume(float value);

	float GetSoundVolume() const;
	float GetMusicVolume() const;
	
	void PlayMusic();
	void StopMusic();
	
	void PlayPixel();
	void PlayBonus(unsigned bonusLevel);
	
	void PlaySound(Sound sound);
	
	bool IsLoaded() const;
};
