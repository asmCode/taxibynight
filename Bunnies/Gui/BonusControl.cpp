#include "BonusControl.h"
#include "../Label.h"
#include "../Bonuses/Bonus.h"
#include "../Inflater.h"
#include "../Environment.h"
#include "../InterfaceProvider.h"
#include "../SpritesMap.h"
#include <Graphics/SpriteBatch.h>
#include <Utils/StringUtils.h>

BonusControl::BonusControl(Bonus* bonus) :
	Control(""),
	m_bonus(bonus)
{
	m_view = Inflater::Inflate(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/gui/BonusControl.xml");

	SetWidth(m_view->GetWidth());
	SetHeight(m_view->GetHeight());

	this->AddChild(m_view);

	m_icon = dynamic_cast<Control*>(m_view->FindChild("icon"));
	m_bonusName = dynamic_cast<Label*>(m_view->FindChild("name"));
	m_timeLeft = dynamic_cast<Label*>(m_view->FindChild("time_left"));

	assert(m_icon != NULL);
	assert(m_bonusName != NULL);
	assert(m_timeLeft != NULL);

	m_bonusName->SetText(m_bonus->GetName());

	TexPart *icon = InterfaceProvider::GetSpritesMap()->GetTexPart(m_bonus->GetIconName());
	m_icon->SetBackground(*icon);
}

void BonusControl::OnUpdate(float time, float ms)
{
	this->Control::OnUpdate(time, ms);

	std::string timeLeftStr = "Time left: ";
	timeLeftStr += StringUtils::ToString((int)m_bonus->GetTimeLeft());

	if (timeLeftStr.size() == 1)
		timeLeftStr = std::string("0") + timeLeftStr;

	m_timeLeft->SetText(timeLeftStr);
}
