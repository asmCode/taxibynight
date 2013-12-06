#pragma once

#include "Control.h"

class AnimButton : public Control
{
private:
	TexPart normalState;
	TexPart pushedState;
	
	bool m_checked;

protected:
	virtual void OnDraw(float time, float ms);

public:
	AnimButton(const std::string &name,
			   float x, float y,
			   TexPart normalState,
			   TexPart pushedState);

	void SetChecked(bool checked);
};
