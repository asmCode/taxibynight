#pragma once

#include "IScreen.h"
#include "IControlEventsObserver.h"

class GameController;
class Control;

class CarDealerScreen :
	public IScreen,
	public IControlEventsObserver
{
public:
	CarDealerScreen(GameController *gameController);
	~CarDealerScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
	GameController *m_gameController;

	Control *m_view;

	Control* m_car1Button;
	Control* m_car2Button;
	Control* m_car3Button;

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void Enter();
};

