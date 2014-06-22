#pragma once

#include "UpgradeData.h"
#include "DecalData.h"
#include "../UpgradeId.h"
#include <string>
#include <vector>

class CarData
{
public:
	std::string Id;
	std::string Name;
	float SoftPrice;
	float HardPrice;
	float Speed;
	float Acc;
	float Tires;
	int SpeedSlots;
	int AccSlots;
	int TiresSlots;
	std::vector<UpgradeData> Upgrades;
	std::vector<DecalData> Decals;

	UpgradeData GetUpgradeData(const std::string& id) const;
	DecalData GetDecalData(const std::string& id) const;

	int GetUpgradeSlotsCount(const std::string& id) const;
};
