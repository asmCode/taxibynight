#pragma once

#include "../Control.h"
#include "../PlayerObserver.h"
#include "../IControlEventsObserver.h"
#include <string>

class Label;
class AnimButton;
class ProgressBar;

class StatusBar : public Control,
				  public PlayerObserver,
				  public IControlEventsObserver
{
public:
	StatusBar(const std::string& name);

private:	
	Control *m_view;

	Label* m_softMoneyLabel;
	Label* m_hardMoneyLabel;
	Label* m_levelLabel;
	ProgressBar* m_experienceBar;
	AnimButton* m_addMoneyButton;

	void Refresh();
	void RefreshExp();

	// PlayerObserver Impl
	void SoftMoneyChanged();
	void HardMoneyChanged();
	void ExperienceChanged();
	void LevelChanged();

	void Clicked(Control *control, uint32_t x, uint32_t y);
};
