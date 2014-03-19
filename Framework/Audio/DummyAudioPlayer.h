#ifndef DUMMY_AUDIO_PLAYER
#define DUMMY_AUDIO_PLAYER

#include "IAudioPlayer.h"

class DummyAudioPlayer : public IAudioPlayer
{
	void Play();
	void Stop();
	
	void SetLoop(bool loop);
	
	void SetVolume(float vol);
	float GetVolume() const;
	void SetPitch(float pitch);
};


#endif // DUMMY_AUDIO_PLAYER