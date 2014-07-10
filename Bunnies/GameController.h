#pragma once

#include <UI/IGestureHandler.h>
#include "IGameController.h"
#include "ISystemUtils.h"
#include <Core/stdint.h>
#include <string>

class IGraphicsEngine;
class IScreen;
class GameScreen;
class SplashScreen;
class MainMenuScreen;
class ComicsScreen;
class IntroScreen;
class SummaryScreen;
class LeaderboardScreen;
class GarageScreen;
class CarDealerScreen;
class CarPartsScreen;
class Content;
class IServiceProvider;

class GameController : public IGameController
{
public:
	GameController(IGraphicsEngine *graphicsEngine);
	virtual ~GameController(void);

	bool Initialize(ISystemUtils *systemUtils, IServiceProvider* serviceProvider);

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(int pointId, const sm::Vec2 &point);
    void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void HandleEnterForeground();
	void HandleEnterBackground();
	void HandleBackButton();
	void HandleMenukButton();

	bool proto_IsInGame();
	void proto_SetStrafeMove(float value);
	void proto_SetForwardMove(float value);
	void proto_SetLookTarget(const sm::Vec3 &lookTarget);

	void ShowGameScreen();
	void ShowGarageScreen();
	void ShowCarDealerScreen();
	void ShowCarPartsScreen();
	void ShowLeaderboard();
	void ShowMainMenuScreen();
	void ShowIntroScreen();
	void ShowSummaryScreen(
		float earn,
		int courses,
		float totalEarn,
		int totalCourses,
		bool record);

private:
	GameScreen *m_gameScreen;
	SplashScreen *m_splashScreen;
	MainMenuScreen *m_mainMenuScreen;
	SummaryScreen *m_summaryScreen;
	ComicsScreen *m_comicsScreen;
	LeaderboardScreen *m_leaderboardScreen;
	GarageScreen *m_garageScreen;
	CarDealerScreen *m_carDealerScreen;
	CarPartsScreen* m_carPartsScreen;
	IntroScreen *m_introScreen;

	IGraphicsEngine *m_graphicsEngine;
	Content *m_content;

	IScreen *m_activeScreen;

	ISystemUtils *m_systemUtils;

	bool InitializeGraphics(const std::string &basePath);
};

