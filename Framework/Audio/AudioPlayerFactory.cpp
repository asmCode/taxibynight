#ifndef _WIN32

#include "AudioPlayerFactory.h"
#include "AlAudioPlayer.h"
#include "TizenAudioPlayer.h"
#include <assert.h>

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

IAudioPlayer* AudioPlayerFactory::CreateTizenAudioPlayer(const std::string &file)
{
	return TizenAudioPlayer::LoadFromFile(file);
}

#endif