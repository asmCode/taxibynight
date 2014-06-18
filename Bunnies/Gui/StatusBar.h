#pragma once

#include "../Control.h"
#include "../PlayerObserver.h"
#include "../IControlEventsObserver.h"
#include <string>

class Label;
class AnimButton;

class StatusBar : public Control,
				  public PlayerObserver,
				  public IControlEventsObserver
{
public:
	StatusBar();

private:	
	Control *m_view;

	Label* m_softMoneyLabel;
	Label* m_hardMoneyLabel;
	AnimButton* m_addMoneyButton;

	void Refresh();

	// PlayerObserver Impl
	void SoftMoneyChanged();
	void HardMoneyChanged();
	void ExperienceChanged();
	void LevelChanged();

	void Clicked(Control *control, uint32_t x, uint32_t y);
};
