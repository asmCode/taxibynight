#include "ParseGameDataAccess.h"
#include "../IRemoteGameDataAccessObserver.h"
#import <Parse/Parse.h>

ParseGameDataAccess::ParseGameDataAccess() :
	m_observer(NULL)
{
	
}

void ParseGameDataAccess::RefreshTopPlayers(LeaderboardType type, int amount)
{
	[PFCloud callFunctionInBackground:@"GetTop"
					   withParameters:@{}
								block:^(NSArray *result, NSError *error) {
									if (!error) {
										ProcessLeaderboardResponse(result, m_leaderboardTop[static_cast<int>(type)]);
										
										if (m_observer != NULL)
											m_observer->TopPlayersRefreshed();
									}
								}];
}

void ParseGameDataAccess::RefreshSurroundPlayers(LeaderboardType type, const std::string& playerId)
{
	
}

void ParseGameDataAccess::SavePlayerStats(const PlayerStats& playerStats)
{
	
}

void ParseGameDataAccess::SetObserver(IRemoteGameDataAccessObserver* observer)
{
	m_observer = observer;
}

const std::vector<PlayerStats>& ParseGameDataAccess::GetTopPlayers(LeaderboardType type) const
{
	return m_leaderboardTop[static_cast<int>(type)];
}

const std::vector<PlayerStats>& ParseGameDataAccess::GetSurroundPlayers(LeaderboardType type) const
{
	return m_leaderboardSurround[static_cast<int>(type)];
}

void ParseGameDataAccess::ProcessLeaderboardResponse(NSArray* dictionary,
													 std::vector<PlayerStats>& playerStatsList)
{
	playerStatsList.clear();
	
	for (PFObject* playerObject in dictionary)
	{
		PlayerStats playerStats;
		
		playerStats.m_id = [playerObject.objectId UTF8String];
		playerStats.m_name = [((NSString*)playerObject[@"name"]) UTF8String];
		playerStats.m_place = 0;
		
//		std::string totalMoneyStr = [((NSString*)playerObject[@"total_money"]) UTF8String];
//		sscanf(totalMoneyStr.c_str(), "%f", &playerStats.m_reward);
		
		playerStats.m_reward = [((NSNumber*)playerObject[@"total_money"]) floatValue];
		
		playerStatsList.push_back(playerStats);
	}
}
