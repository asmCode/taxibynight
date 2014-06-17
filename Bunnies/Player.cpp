#include "Player.h"
#include "PlayerObserver.h"
#include <Utils/StringUtils.h>
#include <IO/Path.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <string>

Player *Player::Instance;

Player::Player(const std::string &path) :
	m_id(""),
	m_name("unnamed"),
	m_hardMoney(0.0f),
	m_totalCourses(0),
	m_bestRoundIncome(0.0f),
	m_tutorialFinished(false),
	m_firstRun(true),
	m_path(path)
{
	Instance = this;
}

void Player::Load()
{
	if (!Path::IsFileExists(m_path.c_str()))
		return;

	XMLNode *node = XMLLoader::LoadFromFile(m_path);
	if (node == NULL)
		return;

	for (int i = 0; i < node->GetChildrenCount(); i++)
	{
		XMLNode *child = node->GetChild(i);
		if (child->GetName() == "SoftMonet")
			m_softMoney = child->GetValueAsFloat();
		else if (child->GetName() == "TotalCourses")
			m_totalCourses = child->GetValueAsInt32();
		else if (child->GetName() == "BestRoundIncome")
			m_bestRoundIncome = child->GetValueAsInt32();
		else if (child->GetName() == "TutorialFinished")
			m_tutorialFinished = child->GetValueAsBool();
		else if (child->GetName() == "FirstRun")
			m_firstRun = child->GetValueAsBool();
		else if (child->GetName() == "Id")
			m_id = child->GetValueAsString();
		else if (child->GetName() == "Name")
			m_name = StringUtils::FromBase64(child->GetValueAsString());
	}
}

void Player::Save()
{
	std::string xml;

	xml += "<Player>\n";
	xml += "\t<Id>"; xml += m_id; xml += "</Id>\n";
	xml += "\t<Name>"; xml += StringUtils::ToBase64(m_name); xml += "</Name>\n";
	xml += "\t<SoftMoney>"; xml += StringUtils::ToString(m_softMoney); xml += "</SoftMoney>\n";
	xml += "\t<TotalCourses>"; xml += StringUtils::ToString(m_totalCourses); xml += "</TotalCourses>\n";
	xml += "\t<BestRoundIncome>"; xml += StringUtils::ToString(m_bestRoundIncome); xml += "</BestRoundIncome>\n";
	xml += "\t<TutorialFinished>"; xml += m_tutorialFinished ? "true" : "false"; xml += "</TutorialFinished>\n";
	xml += "\t<FirstRun>"; xml += m_firstRun ? "true" : "false"; xml += "</FirstRun>\n";
	xml += "</Player>\n";

	Path::WriteTextFile(m_path.c_str(), xml);
}

float Player::GetExperience() const
{
	return m_experience;
}

float Player::GetLevel() const
{
	return fmodf(m_experience, 100.0f);
}

float Player::GetSoftMoney() const
{
	return m_softMoney;
}

float Player::GetHardMoney() const
{
	return m_hardMoney;
}

void Player::SetExperience(float experience)
{
	assert(experience >= 0);

	if (m_experience != experience)
	{
		int prevLevel = GetLevel();

		m_experience = experience;
		NotifyExperienceChanged();

		if (GetLevel() != prevLevel)
			NotifyLevelChanged();
	}
}

void Player::SetSoftMoney(float softMoney)
{
	assert(softMoney >= 0);

	if (m_softMoney != softMoney)
	{
		m_softMoney = softMoney;
		NotifySoftMoneyChanged();
	}
}

void Player::SetHardMoney(float hardMoney)
{
	assert(hardMoney >= 0);

	if (m_hardMoney != hardMoney)
	{
		m_hardMoney = hardMoney;
		NotifyHardMoneyChanged();
	}
}

void Player::AddObserver(PlayerObserver *observer)
{
	m_observers.push_back(observer);
}

void Player::NotifyExperienceChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->ExperienceChanged();
}

void Player::NotifyLevelChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->LevelChanged();
}

void Player::NotifySoftMoneyChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->SoftMoneyChanged();
}

void Player::NotifyHardMoneyChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->HardMoneyChanged();
}
