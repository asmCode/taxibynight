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

	void SetContent(
		float earn,
		int courses,
		float totalEarn,
		int totalCourses);

private:
	Label *m_earnLabel;
	Label *m_coursesLabel;
	Label *m_totalEarnLabel;
	Label *m_totalCoursesLabel;
	bool m_record;

	SummaryPanel();
	
	// Control interface
	void OnDraw(float time, float seconds);

	// IControlEventsObserver interface
	void Clicked(Control *control, uint32_t x, uint32_t y);
};

