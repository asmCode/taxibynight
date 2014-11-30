#pragma once

#include "IScreen.h"
#include "IControlEventsObserver.h"

class GameController;
class StatusBar;
class Control;
class ControlAnimation;
class CarDealerPanelController;

class GarageScreen :
	public IScreen,
	public IControlEventsObserver
{
public:
	GarageScreen(GameController *gameController);
	~GarageScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
	GameController *m_gameController;

	Control *m_garageView;

	Control* m_carDealerButton;
	Control* m_carPartsButton;
	Control* m_carPaintButton;

	CarDealerPanelController* m_carDealerPanelController;

	ControlAnimation* m_viewAnim;

	StatusBar* m_statusBar;

	void ShowCarDealerPanel();

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void Enter();
};

