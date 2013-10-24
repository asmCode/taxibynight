#pragma once

#include "Control.h"
#include "IControlEventsObserver.h"

class GameScreen;
class Label;

class SummaryPanel :
	public Control,
	public IControlEventsObserver
{
public:
	GameScreen *m_gameScreen;

	static SummaryPanel *Create(GameScreen *m_gameScreen);

private:
	/*Label *m_totalMoneyLabel;
	Label *m_totalCoursesLabel;
	Label *m_rewardLabel;
	Label *m_timeLeftLabel;*/

	SummaryPanel();
	
	// Control interface
	void OnDraw(float time, float seconds);

	// IControlEventsObserver interface
	void Clicked(Control *control, uint32_t x, uint32_t y);
};

