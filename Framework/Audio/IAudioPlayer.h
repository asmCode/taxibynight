#pragma once

#include <string>

class IAudioPlayer
{
public:
	virtual ~IAudioPlayer() {}

	virtual bool LoadFromFile(const std::string& file, bool stereo, bool loadIntoMemory) = 0;

	virtual void Update() {}
	
	virtual void Play() = 0;
	virtual void Stop() = 0;
	
	virtual void SetLoop(bool loop) = 0;
	
	virtual void SetVolume(float vol) = 0;
	virtual float GetVolume() const = 0;
	virtual void SetPitch(float pitch) = 0;
};
