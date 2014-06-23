#pragma once

#include "IScreen.h"
#include "IControlEventsObserver.h"

class GameController;
class ProgressControl;
class StatusBar;
class Control;

class CarPartsScreen :
	public IScreen,
	public IControlEventsObserver
{
public:
	CarPartsScreen(GameController *gameController);
	~CarPartsScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
	GameController *m_gameController;

	Control *m_view;

	ProgressControl* m_speedProgress;
	ProgressControl* m_accProgress;
	ProgressControl* m_tiresProgress;

	StatusBar* m_statusBar;

	void RefreshView();

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void Enter();
};

