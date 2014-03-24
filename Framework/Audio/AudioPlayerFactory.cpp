#include "AudioPlayerFactory.h"

#include "DummyAudioPlayer.h"

#ifdef _WIN32
#include "BassPlayer.h"
#elif _TIZEN
#include "AlAudioPlayer.h"
#endif

#include "FModAudioPlayer.h"

#include <assert.h>

IAudioPlayer* AudioPlayerFactory::CreateAudioPlayer(const std::string &file,
													bool stereo,
													bool loadIntoMemory)
{
	return new FModAudioPlayer(file, stereo, loadIntoMemory);
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

IAudioPlayer* AudioPlayerFactory::CreateBassPlayer(const std::string &file)
{
#ifdef _WIN32
	BassPlayer *player = new BassPlayer();
	player->LoadMusic(file.c_str());
	
	return player;
#else
	return NULL;
#endif
}
