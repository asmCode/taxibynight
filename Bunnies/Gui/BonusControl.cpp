#include "BonusControl.h"
#include "../Inflater.h"
#include "../Environment.h"
#include <Graphics/SpriteBatch.h>

BonusControl::BonusControl(
	const std::string &name,
	TexPart icon) :
	Control(name)
{
	m_icon = icon;

	m_view = Inflater::Inflate(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/gui/BonusControl.xml");

	SetWidth(m_view->GetWidth());
	SetHeight(m_view->GetHeight());

	this->AddChild(m_view);
}

/*
void BonusControl::OnDraw(float time, float ms)
{
	sm::Vec2 globalPos = GetGlobalPos();

	TexPart image = m_pressState == PressState_Pressed || m_checked ? pushedState : normalState;
	
	spriteBatch ->Draw(image, (int)globalPos.x, (int)globalPos.y, width, height);
}
*/
