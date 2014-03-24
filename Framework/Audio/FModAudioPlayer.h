#ifndef FMOD_AUDIO_PLAYER
#define FMOD_AUDIO_PLAYER

#include "IAudioPlayer.h"
#include <string>

class FModAudioPlayer : public IAudioPlayer
{
public:
	FModAudioPlayer(const std::string& file, bool stereo, bool loadIntoMemory);

	void Play();
	void Stop();
	
	void SetLoop(bool loop);
	
	void SetVolume(float vol);
	float GetVolume() const;
	void SetPitch(float pitch);
};


#endif // FMOD_AUDIO_PLAYER