#pragma once

#include "IControlEventsObserver.h"
#include "CarObserver.h"
#include <Math/Vec2.h>
#include <string>

class GameController;
class ProgressControl;
class Control;
class Label;
class GridPanel;
class Car;
class AnimButton;

class DecalsPanelController :
	public IControlEventsObserver,
	public CarObserver
{
public:
	DecalsPanelController(GameController *gameController, Control* view);
	~DecalsPanelController(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void RefreshView();
	void Enter();
	void SetActive(bool active);

private:
	GameController *m_gameController;

	Control *m_view;

	Control* m_buyPanel;
	Control* m_activatePanel;

	Control* m_buySoftButton;
	Control* m_buyHardButton;
	Control* m_activateButton;

	GridPanel* m_decalButtonsGrid;

	Label* m_softPriceLabel;
	Label* m_hardPriceLabel;

	std::string m_selectedDecalId;
	Car* m_activeCar;

	void BuyDecal(const std::string& decalId, bool buyForHard);
	void ActivateDecal(const std::string& decalId);
	void SelectDecal(const std::string& decalId);
	void HideAllActionPanels();
	void CreateDecalsButtons();
	AnimButton* CreateDecalButton(const std::string& decalId);

	void HandlePress(int pointId, const sm::Vec2 &point);
	void HandleRelease(int pointId, const sm::Vec2 &point);
	void HandleMove(int pointId, const sm::Vec2 &point);

	void Clicked(Control *control, uint32_t x, uint32_t y);

	void ChangedDecal(Car* car, const std::string& decalId);
};

