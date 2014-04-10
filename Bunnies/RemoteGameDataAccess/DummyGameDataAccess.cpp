#include "DummyGameDataAccess.h"
#include "IRemoteGameDataAccessObserver.h"

DummyGameDataAccess::DummyGameDataAccess() :
	m_observer(NULL)
{

}

void DummyGameDataAccess::RefreshTopPlayers(LeaderboardType type, int amount)
{
}

void DummyGameDataAccess::RefreshSurroundPlayers(LeaderboardType type, const std::string& playerId)
{

}

void DummyGameDataAccess::SavePlayerStats(const PlayerStats& playerStats)
{

}

void DummyGameDataAccess::SetObserver(IRemoteGameDataAccessObserver* observer)
{
	m_observer = observer;
}

const std::vector<PlayerStats>& DummyGameDataAccess::GetTopPlayers(LeaderboardType type) const
{
	static std::vector<PlayerStats> dummy;

	return dummy;
}

const std::vector<PlayerStats>& DummyGameDataAccess::GetSurroundPlayers(LeaderboardType type) const
{
	static std::vector<PlayerStats> dummy;

	return dummy;
}
