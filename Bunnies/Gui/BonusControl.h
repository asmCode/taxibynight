#pragma once

#include "../Control.h"

class Bonus;
class Label;

class BonusControl : public Control
{
public:
	BonusControl(Bonus* bonus);

protected:
	//virtual void OnDraw(float time, float ms);

private:
	Bonus* m_bonus;

	Control *m_view;

	Control* m_icon;
	Label* m_bonusName;
	Label* m_timeLeft;

	void OnUpdate(float time, float ms);
};
