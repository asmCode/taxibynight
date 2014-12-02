#pragma once

#include "IControlEventsObserver.h"
#include "IGaragePanel.h"
#include <Math/Vec2.h>
#include <string>

class GameController;
class ProgressControl;
class Control;
class Label;
class Car;
class GuiCar;

class CarDealerPanelController :
	public IGaragePanel,
	public IControlEventsObserver
{
public:
	CarDealerPanelController(GameController *gameController, Control* view, GuiCar* guiCar);
	~CarDealerPanelController(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void RefreshView();
	void Enter();
	void Leave();
	void SetActive(bool active);

private:
	GameController *m_gameController;
	GuiCar* m_guiCar;
	Control *m_view;

	Control* m_car1Button;
	Control* m_car2Button;
	Control* m_car3Button;

	Control* m_buyPanel;
	Control* m_activatePanel;
	Control* m_alreadyHavePanel;

	Control* m_buySoftButton;
	Control* m_buyHardButton;
	Control* m_activateButton;

	Label* m_softPriceLabel;
	Label* m_hardPriceLabel;
	Label* m_carNameLabel;

	ProgressControl* m_speedProgress;
	ProgressControl* m_accProgress;
	ProgressControl* m_tiresProgress;

	Car* m_activeCar;

	std::string m_selectedCarId;

	void SelectCar(const std::string& carId);
	void BuyCar(const std::string& carId, bool buyForHard);
	void ActivateCar(const std::string& carId);
	void HideAllActionPanels();
	void RefreshCarStatistics();

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);
};

