#pragma once

#include "IScreen.h"
#include "ILeaderboardObserver.h"
#include "IControlEventsObserver.h"
#include "IScreenKeyboardObserver.h"
#include "PlayerStats.h"
#include <Core/stdint.h>
#include <vector>

class Control;
class GameController;
class Label;
class AnimButton;

class LeaderboardScreen : public IScreen, public ILeaderboardObserver, public IControlEventsObserver, public IScreenKeyboardObserver
{
public:
	enum Tab
	{
		Tab_Top,
		Tab_You,
	};

	LeaderboardScreen(GameController *gameController);
	~LeaderboardScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void SetTab(Tab tab);
	void RefreshCurrentView();
	void SetOffline();
	void SetOnline();
	void ClearTable();

private:
	static const int RowHeight = 33;
	static const int PlaceColumnShift = 174;
	static const int NameColumnShift = 300;
	static const int PointsColumnShift = 845;
	static const int LevelColumnShift = 1030;

	Control* m_changeNameButton;
	Control* m_backButton;
	Control* m_refreshButton;
	Label* m_playerNameLabel;

	AnimButton* m_topButton;
	AnimButton* m_youButton;

	GameController *m_gameController;

	Control* m_leaderboardPanel;

	Tab m_currentTab;

	std::vector<Label*> m_tableLabels;

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void ScreenKeyboardDone(const std::string& text);
	void ScreenKeyboardCanceled();

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void Enter();

	void LeaderOffline();
	void LeaderTopLoaded();
	void LeaderPlayerLoaded();
	void PointsUpdated(int playerId);
	void SetPlayerStats(const std::vector<PlayerStats>& playerStats);
};

