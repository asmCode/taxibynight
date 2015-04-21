#include "AudioPlayerFactory.h"

#include "DummyAudioPlayer.h"

#ifdef _WIN32
#elif _TIZEN
#include "AlAudioPlayer.h"
#endif

#include "FModAudioPlayer.h"

#include <assert.h>

IAudioPlayer* AudioPlayerFactory::CreateAudioPlayer(const std::string &file,
													bool stereo,
													bool loadIntoMemory)
{
	/*
	IAudioPlayer *player = new FModAudioPlayer();
	if (player == NULL)
		return NULL;

	if (!player->LoadFromFile(file, stereo, loadIntoMemory))
	{
		delete player;
		return NULL;
	}

	return player;
	*/

	IAudioPlayer *player = new DummyAudioPlayer();
	return player;
}


IAudioPlayer* AudioPlayerFactory::CreateAlAudioPlayer(const std::string &file, bool stereo)
{
#ifdef _TIZEN
	if (!AlAudioPlayer::IsInitialized())
	{
		if (!AlAudioPlayer::Initialize())
		{
			assert(false);
			return NULL;
		}
	}
	
	return AlAudioPlayer::LoadFromFile(file, stereo);
#else
	return NULL;
#endif
}

IAudioPlayer* AudioPlayerFactory::CreateTizenAudioPlayer(const std::string &file)
{
#ifdef _TIZEN
	return TizenAudioPlayer::LoadFromFile(file);
#else
	return NULL;
#endif
}

