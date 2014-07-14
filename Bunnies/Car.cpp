#include "Car.h"
#include "CarObserver.h"
#include <Core/stdint.h>
#include <algorithm>
#include <assert.h>

Car::Car(
	CarData carData,
	int speedUpgradeLevel,
	int accUpgradeLevel,
	int tiresUpgradeLevel,
	const std::vector<DecalData>& decals) :
	m_carData(carData),
	m_speedUpgradeLevel(speedUpgradeLevel),
	m_accUpgradeLevel(accUpgradeLevel),
	m_tiresUpgradeLevel(tiresUpgradeLevel),
	m_decals(decals)
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

int Car::GetUpgradeLevel(const std::string& id) const
{
	if (id == UpgradeId::Speed)
		return m_speedUpgradeLevel;
	if (id == UpgradeId::Acc)
		return m_accUpgradeLevel;
	if (id == UpgradeId::Tires)
		return m_tiresUpgradeLevel;

	assert(false);
	return 0;
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
	else
	{
		assert(false);
	}
}

void Car::GetNextUpgradePrice(const std::string& id, float& softPrice, float& hardPrice) const
{
	UpgradeData upgradeData = m_carData.GetUpgradeData(id);

	int upgradeLevel = GetUpgradeLevel(id);

	if (upgradeData.UpgradeLevels.size() == upgradeLevel)
		return;

	softPrice = upgradeData.UpgradeLevels[upgradeLevel].SoftPrice;
	hardPrice = upgradeData.UpgradeLevels[upgradeLevel].HardPrice;
}

const std::vector<DecalData>& Car::GetDecals() const
{
	return m_decals;
}

void Car::Upgrade(const std::string& upgradeId)
{
	if (IsFullyUpgraded(upgradeId))
		return;

	if (upgradeId == UpgradeId::Speed)
		m_speedUpgradeLevel++;
	if (upgradeId == UpgradeId::Acc)
		m_accUpgradeLevel++;
	if (upgradeId == UpgradeId::Tires)
		m_tiresUpgradeLevel++;

	NotifyUpgraded(upgradeId);
}

bool Car::IsFullyUpgraded(const std::string& upgradeId)
{
	return m_carData.GetUpgradeSlotsCount(upgradeId) == GetUpgradeLevel(upgradeId);
}

void Car::AddDecal(DecalData decalData)
{
	assert(!HasDecal(decalData.Id));
	if (HasDecal(decalData.Id))
		return;

	m_decals.push_back(decalData);
}

void Car::SetDecal(const std::string& decalId)
{
	if (decalId != "")
	{
		assert(HasDecal(decalId));
		if (!HasDecal(decalId))
			return;
	}

	m_activeDecalId = decalId;

	NotifyChangedDecal(decalId);
}

DecalData Car::GetDecal(const std::string& decalId) const
{
	for (uint32_t i = 0; i < m_decals.size(); i++)
	if (m_decals[i].Id == decalId)
		return m_decals[i];

	return DecalData();
}

std::string Car::GetActiveDecalId() const
{
	return m_activeDecalId;
}

float Car::GetActiveDecalBonus() const
{
	if (m_activeDecalId == "")
		return 0.0f;

	DecalData decalData = GetDecal(m_activeDecalId);
	return decalData.Bonus;
}

bool Car::HasDecal(const std::string& decalId) const
{
	for (uint32_t i = 0; i < m_decals.size(); i++)
		if (m_decals[i].Id == decalId)
			return true;

	return false;
}

void Car::AddObserver(CarObserver* carObserver)
{
	if (std::find(m_observers.begin(), m_observers.end(), carObserver) != m_observers.end())
		return;

	m_observers.push_back(carObserver);
}

void Car::NotifyUpgraded(const std::string& upgradeId)
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->Upgraded(this, upgradeId);
}

void Car::NotifyChangedDecal(const std::string& decalId)
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->ChangedDecal(this, decalId);
}
