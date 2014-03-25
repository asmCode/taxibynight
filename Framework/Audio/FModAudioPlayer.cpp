#include "FModAudioPlayer.h"
#include <fmod/fmod.hpp>

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
	m_volume(1.0f),
	m_pitch(1.0f)
{
}

bool FModAudioPlayer::LoadFromFile(const std::string& file, bool stereo, bool loadIntoMemory)
{
	if (!m_isInitialized && !Initialize())
		return false;

	FMOD_RESULT result;

	result = m_system->createSound(file.c_str(), FMOD_2D | FMOD_HARDWARE | FMOD_LOOP_NORMAL, NULL, &m_sound);
	if (result != FMOD_OK)
		return false;

	SetLoop(false);

	return true;
}

void FModAudioPlayer::Play()
{
	m_system->playSound(m_sound, NULL, false, &m_channel);

	m_system->update();
	
	SetVolume(m_volume);
	SetPitch(m_pitch);
}

void FModAudioPlayer::Stop()
{
	if (m_channel != NULL)
	{
		m_channel->stop();
		m_channel = NULL;

		m_system->update();
	}
}

void FModAudioPlayer::SetLoop(bool loop)
{
	m_sound->setLoopCount(loop ? -1 : 0);
	m_system->update();
}

void FModAudioPlayer::SetVolume(float vol)
{
	m_volume = vol;

	if (m_channel != NULL)
	{
		m_channel->setVolume(m_volume);
		m_system->update();
	}
}

float FModAudioPlayer::GetVolume() const
{
	return m_volume;
}

void FModAudioPlayer::SetPitch(float pitch)
{
	m_pitch = pitch;

	if (m_channel != NULL)
	{
		m_channel->setPitch(m_pitch);
		m_system->update();
	}
}
