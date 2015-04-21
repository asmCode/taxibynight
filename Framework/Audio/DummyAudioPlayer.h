#ifndef DUMMY_AUDIO_PLAYER
#define DUMMY_AUDIO_PLAYER

#include "IAudioPlayer.h"

class DummyAudioPlayer : public IAudioPlayer
{
public:
	bool Initialize();

	bool LoadFromFile(const std::string& file, bool stereo, bool loadIntoMemory) {};

	void Play();
	void Stop();
	
	void SetLoop(bool loop);
	
	void SetVolume(float vol);
	float GetVolume() const;
	void SetPitch(float pitch);
};


#endif // DUMMY_AUDIO_PLAYER
