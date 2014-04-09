#ifndef LEADERBOARDOBSERVER_H_
#define LEADERBOARDOBSERVER_H_

#include <string>

class ILeaderboardObserver
{
public:
	virtual ~ILeaderboardObserver() {}

	virtual void LeaderOffline() = 0;
	virtual void LeaderTopLoaded() = 0;
	virtual void LeaderPlayerLoaded() = 0;
	virtual void PointsUpdated(const std::string& playerId) = 0;
};

#endif /* LEADERBOARDOBSERVER_H_ */
