#include "StatusBar.h"
#include "../Label.h"
#include "../AnimButton.h"
#include "../Inflater.h"
#include "../Environment.h"
#include "../InterfaceProvider.h"
#include "../SpritesMap.h"
#include "../Player.h"
#include <Graphics/SpriteBatch.h>
#include <Utils/StringUtils.h>

StatusBar::StatusBar() :
	Control("")
{
	m_view = Inflater::Inflate(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/gui/StatusBar.xml");

	m_view->Update(0, 0); // update width and height
	SetWidth(m_view->GetWidth());
	SetHeight(m_view->GetHeight());

	this->AddChild(m_view);

	m_softMoneyLabel = dynamic_cast<Label*>(m_view->FindChild("soft"));
	m_hardMoneyLabel = dynamic_cast<Label*>(m_view->FindChild("hard"));
	m_addMoneyButton = dynamic_cast<AnimButton*>(m_view->FindChild("add"));

	assert(m_softMoneyLabel != NULL);
	assert(m_hardMoneyLabel != NULL);
	assert(m_addMoneyButton != NULL);

	ObsCast(IControlEventsObserver, m_addMoneyButton)->AddObserver(this);

	Player::Instance->AddObserver(this);

	Refresh();
}

void StatusBar::Refresh()
{
	m_softMoneyLabel->SetText(StringUtils::ToString(Player::Instance->GetSoftMoney()));
	m_hardMoneyLabel->SetText(StringUtils::ToString(Player::Instance->GetHardMoney()));
}

void StatusBar::SoftMoneyChanged()
{
	Refresh();
}

void StatusBar::HardMoneyChanged()
{
	Refresh();
}

void StatusBar::ExperienceChanged()
{
	Refresh();
}

void StatusBar::LevelChanged()
{
	Refresh();
}

void StatusBar::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_addMoneyButton)
	{
		//SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		Player::Instance->SetSoftMoney(Player::Instance->GetSoftMoney() + 100);
		Player::Instance->SetHardMoney(Player::Instance->GetHardMoney() + 10);
	}
}
