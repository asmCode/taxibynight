#pragma once

#include "Control.h"
#include "IControlEventsObserver.h"
#include "Bonuses/IBonusesManagerObserver.h"

class GameScreen;
class Label;
class GridPanel;
class BonusControl;

class HUD :
	public Control,
	public IControlEventsObserver,
	public IBonusesManagerObserver
{
public:
	GameScreen *m_gameScreen;

	static HUD *Create(GameScreen *m_gameScreen);

private:
	Label *m_totalMoneyLabel;
	Label *m_totalCoursesLabel;
	Label *m_rewardLabel;
	Label *m_timeLeftLabel;

	GridPanel* m_bonusesGrid;

	HUD();
	
	// Control interface
	void OnDraw(float time, float seconds);
	void OnUpdate(float time, float seconds);

	// IControlEventsObserver interface
	void Clicked(Control *control, uint32_t x, uint32_t y);
	void Pressed(Control *control, uint32_t x, uint32_t y);
	void Released(Control *control, uint32_t x, uint32_t y);

	void BonusActivated(BonusType bonusType);
	void BonusDeactivated(BonusType bonusType);

	BonusControl* GetBonusControlOfType(BonusType type);
};

