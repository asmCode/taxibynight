#pragma once

#include "IScreen.h"
#include <Graphics/Texture.h>

class GameController;
class MainMenuPanel;

class MainMenuScreen : public IScreen
{
public:
	MainMenuScreen(GameController *gameController);
	~MainMenuScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
	GameController *m_gameController;

	MainMenuPanel *m_mainMenuPanel;

	void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleTapGesture(const sm::Vec2 &point);
};

