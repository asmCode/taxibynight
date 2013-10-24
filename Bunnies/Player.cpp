#include "Player.h"
#include <Utils/StringUtils.h>
#include <IO/Path.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <string>

Player *Player::Instance;

Player::Player(const std::string &path) :
	m_totalMoney(0.0f),
	m_totalCourses(0.0f),
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
		if (child->GetName() == "TotalMoney")
			m_totalMoney = child->GetValueAsFloat();
		else if (child->GetName() == "TotalCourses")
			m_totalCourses = child->GetValueAsInt32();
	}
}

void Player::Save()
{
	std::string xml;

	xml += "<Player>\n";
	xml += "\t<TotalMoney>"; xml += StringUtils::ToString(m_totalMoney); xml += "</TotalMoney>\n";
	xml += "\t<TotalCourses>"; xml += StringUtils::ToString(m_totalCourses); xml += "</TotalCourses>\n";
	xml += "</Player>\n";

	Path::WriteTextFile(m_path.c_str(), xml);
}
