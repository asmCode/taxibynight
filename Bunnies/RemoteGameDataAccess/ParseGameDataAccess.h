#ifndef PARSE_GAME_DATA_ACCESS
#define PARSE_GAME_DATA_ACCESS

#include "../PlayerStats.h"
#include "IRemoteGameDataAccess.h"
#include "LeaderboardType.h"
#include <string>
#import <Foundation/NSArray.h>

class ParseGameDataAccess : public IRemoteGameDataAccess
{
public:
	ParseGameDataAccess();
	
	void RefreshTopPlayers(LeaderboardType type, int amount);
	void RefreshSurroundPlayers(LeaderboardType type, const std::string& playerId);
	void SavePlayerStats(const PlayerStats& playerStats);
	
	void SetObserver(IRemoteGameDataAccessObserver* observer);
	
	const std::vector<PlayerStats>& GetTopPlayers(LeaderboardType type) const;
	const std::vector<PlayerStats>& GetSurroundPlayers(LeaderboardType type) const;
	
private:
	IRemoteGameDataAccessObserver* m_observer;

	std::vector<PlayerStats> m_leaderboardTop[3];
	std::vector<PlayerStats> m_leaderboardSurround[3];
	
	void ProcessLeaderboardResponse(NSArray* dictionary,
									std::vector<PlayerStats>& playerStatsList);
};

#endif // PARSE_GAME_DATA_ACCESS

