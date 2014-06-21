#include "Car.h"

Car::Car() :
	m_speedUpgradeLevel(0),
	m_accUpgradeLevel(0),
	m_tiresUpgradeLevel(0)
{

}

std::string Car::GetId() const
{
	return m_carData.Id;
}

std::string Car::GetName() const
{
	return m_carData.Name;
}

float Car::GetSpeed() const
{
	if (m_speedUpgradeLevel > 0)
		return m_carData.GetUpgradeData(UpgradeId::Speed).UpgradeLevels[m_speedUpgradeLevel - 1].Value;
	else
		return m_carData.Speed;
}

float Car::GetAcc() const
{
	if (m_accUpgradeLevel > 0)
		return m_carData.GetUpgradeData(UpgradeId::Acc).UpgradeLevels[m_accUpgradeLevel - 1].Value;
	else
		return m_carData.Acc;
}

float Car::GetTires() const
{
	if (m_tiresUpgradeLevel > 0)
		return m_carData.GetUpgradeData(UpgradeId::Tires).UpgradeLevels[m_tiresUpgradeLevel - 1].Value;
	else
		return m_carData.Tires;
}

void Car::GetUpgradeSlots(const std::string& id, int& totalSlots, int& activeSlots) const
{
	UpgradeData upgradeData = m_carData.GetUpgradeData(id);

	if (id == UpgradeId::Speed)
	{
		totalSlots = m_carData.SpeedSlots;
		activeSlots = totalSlots - upgradeData.UpgradeLevels.size() + m_speedUpgradeLevel;
	}
	else if (id == UpgradeId::Acc)
	{
		totalSlots = m_carData.AccSlots;
		activeSlots = totalSlots - upgradeData.UpgradeLevels.size() + m_accUpgradeLevel;
	}
	else if (id == UpgradeId::Tires)
	{
		totalSlots = m_carData.TiresSlots;
		activeSlots = totalSlots - upgradeData.UpgradeLevels.size() + m_tiresUpgradeLevel;
	}
}

void Car::GetNextUpgradePrice(const std::string& id, float& softPrice, float& hardPrice)
{
	UpgradeData upgradeData = m_carData.GetUpgradeData(id);

	if (upgradeData.UpgradeLevels.size() == m_speedUpgradeLevel)
		return;

	int upgradeLevel = GetUpgradeLevel(id);

	softPrice = upgradeData.UpgradeLevels[upgradeLevel].SoftPrice;
	hardPrice = upgradeData.UpgradeLevels[upgradeLevel].HardPrice;
}

int Car::GetUpgradeLevel(const std::string& id)
{
	if (id == UpgradeId::Speed)
		return m_speedUpgradeLevel;
	if (id == UpgradeId::Acc)
		return m_accUpgradeLevel;
	if (id == UpgradeId::Tires)
		return m_tiresUpgradeLevel;

	return 0;
}
