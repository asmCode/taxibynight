#pragma once

#include "Control.h"

class AnimButton : public Control
{
private:
	TexPart normalState;
	TexPart pushedState;
	TexPart shadow;
	
protected:
	void OnDraw(float time, float ms);
	void OnTouchBegin(int x, int y);
	void OnTouchEnd(int x, int y);

	
public:
	sm::Vec2 pushedShift;
	sm::Vec2 currentShift;
	
	AnimButton(const std::string &name,
			   float x, float y,
			   TexPart normalState,
			   TexPart pushedState,
			   TexPart shadow);

	AnimButton(const std::string &name,
		       float x, float y,
			   TexPart normalState,
			   TexPart pushedState);
	
};
