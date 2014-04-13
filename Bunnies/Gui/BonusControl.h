#pragma once

#include "../Control.h"

class BonusControl : public Control
{
public:
	BonusControl(
		const std::string &name,
		TexPart icon);

protected:
	//virtual void OnDraw(float time, float ms);

private:
	TexPart m_icon;

	Control *m_view;
};
