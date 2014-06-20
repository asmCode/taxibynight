#pragma once

#include "UpgradeLevelData.h"
#include <string>
#include <vector>

class UpgradeData
{
public:
	std::string Id;
	std::vector<UpgradeLevelData> UpgradeLevels;
};
