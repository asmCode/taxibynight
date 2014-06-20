#include "GlobalSettings.h"
#include <Core/stdint.h>
#include <XML/XMLNode.h>
#include <XML/XMLLoader.h>
#include <assert.h>

std::vector<CarData> GlobalSettings::m_cars;

bool GlobalSettings::LoadFromFile(const std::string& filename)
{
	XMLNode *rootNode = XMLLoader::LoadFromFile(filename);
	if (rootNode == NULL)
		return false;

	XMLNode& carsNode = (*rootNode)["Cars"];

	for (uint32_t i = 0; i < carsNode.GetChildrenCount(); i++)
		m_cars.push_back(LoadCarData(carsNode.GetChild(i)));

	return true;
}

CarData GlobalSettings::GetCarById(const std::string& id)
{
	for (uint32_t i = 0; i < m_cars.size(); i++)
		if (m_cars[i].Id == id)
			return m_cars[i];

	assert(false);
	return CarData();
}

CarData GlobalSettings::LoadCarData(XMLNode* node)
{
	CarData data;

	data.Id = node->GetAttribAsString("id");
	data.Name = node->GetAttribAsString("name");
	data.SoftPrice = node->GetAttribAsFloat("soft_price");
	data.HardPrice = node->GetAttribAsFloat("hard_price");
	data.Speed = node->GetAttribAsFloat("speed");
	data.Acc = node->GetAttribAsFloat("acc");
	data.Tires = node->GetAttribAsFloat("tires");
	data.SpeedSlots = node->GetAttribAsUInt32("speed_slots");
	data.AccSlots = node->GetAttribAsUInt32("acc_slots");
	data.TiresSlots = node->GetAttribAsUInt32("tires_slots");

	XMLNode& upgradesNode = (*node)["Upgrades"];

	for (uint32_t i = 0; i < upgradesNode.GetChildrenCount(); i++)
		data.Upgrades.push_back(LoadUpgradeData(upgradesNode.GetChild(i)));

	assert(data.Id.size() > 0);

	return data;
}

UpgradeData GlobalSettings::LoadUpgradeData(XMLNode* node)
{
	UpgradeData data;

	data.Id = node->GetAttribAsString("id");
	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
		data.UpgradeLevels.push_back(LoadUpgradeLevelData(node->GetChild(i)));

	assert(data.Id.size() > 0);

	return data;
}

UpgradeLevelData GlobalSettings::LoadUpgradeLevelData(XMLNode* node)
{
	UpgradeLevelData data;

	data.Value = node->GetAttribAsFloat("value");
	data.SoftPrice = node->GetAttribAsFloat("soft_price");
	data.HardPrice = node->GetAttribAsFloat("hard_price");

	return data;
}

DecalData GlobalSettings::LoadDecalData(XMLNode* node)
{
	DecalData data;

	data.Id = node->GetAttribAsString("id");
	data.SoftPrice = node->GetAttribAsFloat("soft_price");
	data.HardPrice = node->GetAttribAsFloat("hard_price");
	data.Bonus = node->GetAttribAsFloat("bonus");

	assert(data.Id.size() > 0);

	return data;
}
