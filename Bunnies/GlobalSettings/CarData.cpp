#include "CarData.h"
#include "Core/stdint.h"
#include <assert.h>

UpgradeData CarData::GetUpgradeData(const std::string& id) const
{
	for (uint32_t i = 0; i < Upgrades.size(); i++)
	if (Upgrades[i].Id == id)
		return Upgrades[i];

	assert(false);
	return UpgradeData();
}

DecalData CarData::GetDecalData(const std::string& id) const
{
	for (uint32_t i = 0; i < Decals.size(); i++)
	if (Decals[i].Id == id)
		return Decals[i];

	assert(false);
	return DecalData();
}

int CarData::GetUpgradeSlotsCount(const std::string& id) const
{
	if (id == UpgradeId::Speed)
		return SpeedSlots - GetUpgradeData(id).UpgradeLevels.size();
	else if (id == UpgradeId::Acc)
		return AccSlots - GetUpgradeData(id).UpgradeLevels.size();
	else if (id == UpgradeId::Tires)
		return TiresSlots - GetUpgradeData(id).UpgradeLevels.size();

	assert(false);
	return 0;
}
