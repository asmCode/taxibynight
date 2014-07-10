#pragma once

#include "IScreen.h"
#include "IControlEventsObserver.h"
#include "CarObserver.h"

class GameController;
class ProgressControl;
class StatusBar;
class Control;
class Label;
class Car;

class CarPartsScreen :
	public IScreen,
	public IControlEventsObserver,
	public CarObserver
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

	Control* m_backButton;

	Control* m_buySpeedButton;
	Control* m_buyAccButton;
	Control* m_buyTiresButton;

	Label* m_speedPrice;
	Label* m_accPrice;
	Label* m_tiresPrice;

	ProgressControl* m_speedProgress;
	ProgressControl* m_accProgress;
	ProgressControl* m_tiresProgress;

	StatusBar* m_statusBar;

	Car* m_activeCar;

	void RefreshView();
	void RefreshUpgradeProgress(
		const std::string& upgradeId,
		ProgressControl* progressControl,
		Label* upgradePrice);

	void Upgrade(const std::string& upgradeId);

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void Enter();

	void Upgraded(Car* car, const std::string& upgradeId);
};

