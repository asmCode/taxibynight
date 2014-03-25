#ifndef FMOD_AUDIO_PLAYER
#define FMOD_AUDIO_PLAYER

#include "IAudioPlayer.h"
#include <string>

namespace FMOD { class System; }
namespace FMOD { class Sound; }
namespace FMOD { class Channel; }

class FModAudioPlayer : public IAudioPlayer
{
public:
	FModAudioPlayer();

	bool LoadFromFile(const std::string& file, bool stereo, bool loadIntoMemory);

	void Update();

	void Play();
	void Stop();
	
	void SetLoop(bool loop);
	
	void SetVolume(float vol);
	float GetVolume() const;
	void SetPitch(float pitch);

private:
	static bool m_isInitialized;
	static FMOD::System *m_system;

	FMOD::Sound *m_sound;
	FMOD::Channel *m_channel;

	bool m_isLooping;
	float m_volume;
	float m_pitch;

	static bool Initialize();
};


#endif // FMOD_AUDIO_PLAYER

