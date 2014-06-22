#pragma once

#include "CarData.h"
#include "UpgradeData.h"
#include "UpgradeLevelData.h"
#include "DecalData.h"
#include <string>
#include <vector>

class XMLNode;

class GlobalSettings
{
public:
	static bool LoadFromFile(const std::string& filename);

	static CarData GetCarById(const std::string& id);
	
private:
	static std::vector<CarData> m_cars;

	static CarData LoadCarData(XMLNode* node);
	static UpgradeData LoadUpgradeData(XMLNode* node);
	static UpgradeLevelData LoadUpgradeLevelData(XMLNode* node);
	static DecalData LoadDecalData(XMLNode* node);
};

