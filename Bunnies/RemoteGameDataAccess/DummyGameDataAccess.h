#ifndef DUMMY_GAME_DATA_ACCESS
#define DUMMY_GAME_DATA_ACCESS

#include "../PlayerStats.h"
#include "IRemoteGameDataAccess.h"
#include "LeaderboardType.h"
#include <string>

class DummyGameDataAccess : public IRemoteGameDataAccess
{
public:
	DummyGameDataAccess();
	
	void RefreshTopPlayers(LeaderboardType type, int amount);
	void RefreshSurroundPlayers(LeaderboardType type, const std::string& playerId);
	void SavePlayerStats(const PlayerStats& playerStats);
	
	void SetObserver(IRemoteGameDataAccessObserver* observer);
	
	const std::vector<PlayerStats>& GetTopPlayers(LeaderboardType type) const;
	const std::vector<PlayerStats>& GetSurroundPlayers(LeaderboardType type) const;
	
private:
	IRemoteGameDataAccessObserver* m_observer;
};

#endif // DUMMY_GAME_DATA_ACCESS

