#ifndef IREMOTE_GAME_DATA_ACCESS
#define IREMOTE_GAME_DATA_ACCESS

#include "LeaderboardType.h"
#include "../PlayerStats.h"
#include <vector>
#include <string>

class PlayerStats;
class IRemoteGameDataAccessObserver;

class IRemoteGameDataAccess
{
public:
	virtual ~IRemoteGameDataAccess() {}
	
	virtual void RefreshTopPlayers(LeaderboardType type, int amount) {};
	virtual void RefreshSurroundPlayers(LeaderboardType type, const std::string& playerId) {} ;
	virtual void SavePlayerStats(const PlayerStats& playerStats) = 0;
	
	virtual void SetObserver(IRemoteGameDataAccessObserver* observer) = 0;
	
	virtual const std::vector<PlayerStats>& GetTopPlayers(LeaderboardType type) const = 0;
	virtual const std::vector<PlayerStats>& GetSurroundPlayers(LeaderboardType type) const = 0;
};

#endif // IREMOTE_GAME_DATA_ACCESS

