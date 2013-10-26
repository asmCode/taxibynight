#include "AudioPlayerFactory.h"
#include "AlAudioPlayer.h"

IAudioPlayer* AudioPlayerFactory::CreateAlAudioPlayer(const std::string &file, bool stereo)
{
	if (!AlAudioPlayer::IsInitialized())
	{
		if (!AlAudioPlayer::Initialize())
		{
			assert(false);
			return NULL;
		}
	}
	
	return AlAudioPlayer::LoadFromFile(file, stereo);
}
