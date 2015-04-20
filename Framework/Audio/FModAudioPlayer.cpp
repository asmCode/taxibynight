#include "FModAudioPlayer.h"

#ifdef __ANDROID__
#include <fmod_android/fmod.hpp>
#else
#include <fmod/fmod.hpp>
#endif

bool FModAudioPlayer::m_isInitialized;
FMOD::System *FModAudioPlayer::m_system;

bool FModAudioPlayer::Initialize()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_system);
	if (result != FMOD_OK)
		return false;

	result = m_system->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		delete m_system;
		return false;
	}

	m_isInitialized = true;

	return true;
}

FModAudioPlayer::FModAudioPlayer() :
	m_sound(NULL),
	m_channel(NULL),
	m_isLooping(false),
	m_volume(1.0f),
	m_pitch(1.0f)
{
}

bool FModAudioPlayer::LoadFromFile(const std::string& file, bool stereo, bool loadIntoMemory)
{
	if (!m_isInitialized && !Initialize())
		return false;

	FMOD_RESULT result;

	FMOD_MODE useStream = loadIntoMemory ? 0 : FMOD_CREATESTREAM;

	result = m_system->createSound(
		file.c_str(),
		FMOD_2D | FMOD_LOOP_NORMAL | useStream,
		NULL,
		&m_sound);

	if (result != FMOD_OK)
		return false;

	return true;
}

void FModAudioPlayer::Update()
{
	if (m_system == NULL)
		return;

	m_system->update();
}

void FModAudioPlayer::Play()
{
	if (m_sound == NULL)
		return;

	m_system->playSound(m_sound, NULL, true, &m_channel);

	SetLoop(m_isLooping);
	SetVolume(m_volume);
	SetPitch(m_pitch);

	m_channel->setPaused(false);
}

void FModAudioPlayer::Stop()
{
	if (m_channel == NULL)
		return;

	m_channel->setPaused(true);
}

void FModAudioPlayer::SetLoop(bool loop)
{
	m_isLooping = loop;

	if (m_channel == NULL)
		return;

	m_channel->setLoopCount(m_isLooping ? -1 : 0);
}

void FModAudioPlayer::SetVolume(float vol)
{
	if (m_channel == NULL)
		return;

	m_volume = vol;
	m_channel->setVolume(m_volume);
}

float FModAudioPlayer::GetVolume() const
{
	return m_volume;
}

void FModAudioPlayer::SetPitch(float pitch)
{
	if (m_channel == NULL)
		return;

	m_pitch = pitch;
	m_channel->setPitch(m_pitch);
}

