#ifndef IREMOTE_GAME_DATA_ACCESS_OBSERVER
#define IREMOTE_GAME_DATA_ACCESS_OBSERVER

#include <string>

class IRemoteGameDataAccessObserver
{
public:
	virtual void TopPlayersRefreshed() = 0;
	virtual void SurroundPlayersRefreshed() = 0;
	virtual void PlayerDataSaved(const std::string& playerId) = 0;
};

#endif // IREMOTE_GAME_DATA_ACCESS_OBSERVER

