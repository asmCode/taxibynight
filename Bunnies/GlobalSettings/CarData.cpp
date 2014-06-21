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
