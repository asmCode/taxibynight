#include "Bonus.h"

Bonus::Bonus(BonusType bonusType, float time) :
	m_bonusType(bonusType),
	m_timeLeft(time)
{
}

Bonus::~Bonus()
{

}

BonusType Bonus::GetBonusType() const
{
	return m_bonusType;
}

std::string Bonus::GetName() const
{
	switch (m_bonusType)
	{
	case BonusType_Money:
		return "Money For Nothing";
	case BonusType_Carmageddon:
		return "Carmageddon";
	case BonusType_PedsAntiMagnet:
		return "Peds Anti-Magnet";
	case BonusType_GenerousClients:
		return "Generous Clients";
	case BonusType_FeelThePower:
		return "Feel The Power!";
	case BonusType_TakeYourTime:
		return "Take Your Time";
	case BonusType_VitaminOverdose:
		return "Vitamins Overdose";
	case BonusType_Blind:
		return "Blind";
	case BonusType_ZombiePeds:
		return "Zombie Peds";
	default:
		return "";
	}
}

std::string Bonus::GetIconName() const
{
	switch (m_bonusType)
	{
	case BonusType_Money:
		assert(false);
		return"";
	case BonusType_Carmageddon:
		return "carmageddon";
	case BonusType_PedsAntiMagnet:
		return "peds_antimagnet";
	case BonusType_GenerousClients:
		return "generous_clients";
	case BonusType_FeelThePower:
		return "feel_the_power";
	case BonusType_TakeYourTime:
		return "take_your_time";
	case BonusType_VitaminOverdose:
		return "vitamins_overdose";
	case BonusType_Blind:
		return "blind";
	case BonusType_ZombiePeds:
		return "zombie_peds";
	default:
		return "";
	}
}

float Bonus::GetTimeLeft() const
{
	return m_timeLeft;
}

bool Bonus::IsInstantBonus() const
{
	switch (m_bonusType)
	{
	case BonusType_Money:
		return true;

	case BonusType_TakeYourTime:
	case BonusType_Carmageddon:
	case BonusType_PedsAntiMagnet:
	case BonusType_GenerousClients:
	case BonusType_FeelThePower:
	case BonusType_VitaminOverdose:
	case BonusType_Blind:
	case BonusType_ZombiePeds:
		return false;

	default:
		return false;
	}
}

bool Bonus::IsRunDown() const
{
	return GetTimeLeft() == 0.0f;
}

