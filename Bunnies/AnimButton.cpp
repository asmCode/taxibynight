#include "AnimButton.h"
#include <Graphics/SpriteBatch.h>

AnimButton::AnimButton(const std::string &name,
					   float x, float y,
					   TexPart normalState,
					   TexPart pushedState,
					   TexPart shadow) :
	Control(m_name)
{
	this->x = x;
	this->y = y;
	this->width = normalState.ImageRect.Width;
	this->height = normalState.ImageRect.Height;
	pushedShift = sm::Vec2(0, 0);
	currentShift = sm::Vec2(0, 0); 
	
	this->normalState = normalState;
	this->bg = normalState;
	this->pushedState = pushedState;
	this->shadow = shadow;
}

AnimButton::AnimButton(const std::string &name,
					   float x, float y,
					   TexPart normalState,
					   TexPart pushedState) :
	Control(name)
{
	this->x = x;
	this->y = y;
	this->width = normalState.ImageRect.Width;
	this->height = normalState.ImageRect.Height;
	pushedShift = sm::Vec2(0, 0);
	currentShift = sm::Vec2(0, 0); 
	
	this->normalState = normalState;
	this->bg = normalState;
	this->pushedState = pushedState;
	this->shadow = TexPart();
}

void AnimButton::OnDraw(float time, float ms)
{
	sm::Vec2 globalPos = GetGlobalPos();
	
	if (shadow.Tex != NULL)
		spriteBatch ->Draw(shadow, (int)globalPos.x + 5, (int)globalPos.y + 10);
	spriteBatch ->Draw(bg, (int)globalPos.x + currentShift.x, (int)globalPos.y + currentShift.y);
}

void AnimButton::OnTouchBegin(int x, int y)
{
	this->Control::OnTouchBegin(x, y);

	bg = pushedState;
	currentShift = pushedShift;
}

void AnimButton::OnTouchEnd(int x, int y)
{
	this->Control::OnTouchEnd(x, y);

	bg = normalState;
	currentShift = sm::Vec2(0, 0);
}
