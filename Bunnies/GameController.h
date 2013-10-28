#pragma once

#include <UI/IGestureHandler.h>
#include "IGameController.h"
#include <Core/stdint.h>
#include <string>

class IGraphicsEngine;
class IScreen;
class GameScreen;
class SplashScreen;
class MainMenuScreen;
class SummaryScreen;
class Content;

class GameController : public IGameController
{
public:
	GameController(IGraphicsEngine *graphicsEngine);
	virtual ~GameController(void);

	bool Initialize();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandlePress(int pointId, const sm::Vec2 &point);
    void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	bool proto_IsInGame();
	void proto_SetStrafeMove(float value);
	void proto_SetForwardMove(float value);
	void proto_SetLookTarget(const sm::Vec3 &lookTarget);

	void ShowGameScreen();
	void ShowMainMenuScreen();
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

	IGraphicsEngine *m_graphicsEngine;
	Content *m_content;

	IScreen *m_activeScreen;

	bool InitializeGraphics(const std::string &basePath);
};

