#include "Leaderboard.h"
#include "ILeaderboardObserver.h"
#include "RemoteGameDataAccess/RemoteDataAccessFactory.h"
#include "RemoteGameDataAccess/IRemoteGameDataAccess.h"
#include <Utils/StringUtils.h>
#include <Utils/Log.h>
#include <Math/MathUtils.h>
#include <math.h>
#include <stdio.h>

Leaderboard* Leaderboard::m_instance;

Leaderboard::Leaderboard()
{
	m_remoteDataAccess = RemoteDataAccessFactory::Create();

	m_remoteDataAccess->SetObserver(this);
}

Leaderboard::~Leaderboard()
{
}

Leaderboard* Leaderboard::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new Leaderboard();

	return m_instance;
}

void Leaderboard::AddObserver(ILeaderboardObserver* observer)
{
	m_observers.push_back(observer);
}

void Leaderboard::RefreshTopLadder(LeaderboardType type)
{
	m_remoteDataAccess->RefreshTopPlayers(type, TopCount);
}

void Leaderboard::RefreshSurrLadder(LeaderboardType type, const std::string& playerId)
{
	m_remoteDataAccess->RefreshSurroundPlayers(type, playerId);
}

void Leaderboard::SendPlayerPoints(const PlayerStats& playerStats)
{
	m_remoteDataAccess->SavePlayerStats(playerStats);
}

const std::vector<PlayerStats>& Leaderboard::GetTopLadder(LeaderboardType type) const
{
	return m_remoteDataAccess->GetTopPlayers(type);
}

const std::vector<PlayerStats>& Leaderboard::GetPlayerLadder(LeaderboardType type) const
{
	return m_remoteDataAccess->GetSurroundPlayers(type);
}

void Leaderboard::Timeount()
{
	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->LeaderOffline();
}

void Leaderboard::TopPlayersRefreshed()
{
	for (unsigned int i = 0; i < m_observers.size(); i++)
		m_observers[i]->LeaderTopLoaded();
}

void Leaderboard::SurroundPlayersRefreshed()
{
	int d = 0;
	d++;
	
}

void Leaderboard::PlayerDataSaved(const std::string& playerId)
{
	int d = 0;
	d++;
}
