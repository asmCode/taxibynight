#ifndef LEADERBOARD_H_
#define LEADERBOARD_H_

#include "PlayerStats.h"
#include "RemoteGameDataAccess/IRemoteGameDataAccessObserver.h"
#include "RemoteGameDataAccess/LeaderboardType.h"
#include <string>
#include <vector>

class IRemoteGameDataAccess;
class ILeaderboardObserver;

class Leaderboard : public IRemoteGameDataAccessObserver
{
public:
	static Leaderboard* m_instance;

	virtual ~Leaderboard();

	static Leaderboard* GetInstance();

	void AddObserver(ILeaderboardObserver* observer);

	void RefreshTopLadder(LeaderboardType type);
	void RefreshSurrLadder(LeaderboardType type, const std::string& playerId);
	void SendPlayerPoints(const PlayerStats& playerStats);

	const std::vector<PlayerStats>& GetTopLadder(LeaderboardType type) const;
	const std::vector<PlayerStats>& GetPlayerLadder(LeaderboardType type) const;

private:
	static const int TopCount = 10;
	static const int SurrCount = 5;

	std::vector<ILeaderboardObserver*> m_observers;
	
	IRemoteGameDataAccess* m_remoteDataAccess;
	
	Leaderboard();
	void Initialize();

	void Timeount();
	
	void TopPlayersRefreshed();
	void SurroundPlayersRefreshed();
	void PlayerDataSaved(const std::string& playerId);
};

#endif /* LEADERBOARD_H_ */
