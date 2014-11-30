#pragma once

#include "UpgradeId.h"
#include "GlobalSettings/CarData.h"
#include "GlobalSettings/DecalData.h"
#include <string>
#include <vector>

class CarObserver;

class Car
{
public:
	Car(CarData carData,
		int speedUpgradeLevel,
		int accUpgradeLevel,
		int tiresUpgradeLevel,
		const std::vector<DecalData>& decals);

	std::string GetId() const;
	std::string GetName() const;

	// Speed with upgrades
	float GetSpeed() const;

	// Acc with upgrades
	float GetAcc() const;

	// Tires with upgrades
	float GetTires() const;

	int GetUpgradeLevel(const std::string& id) const;
	void GetUpgradeSlots(const std::string& id, int& totalSlots, int& activeSlots) const;
	void GetNextUpgradePrice(const std::string& id, float& softPrice, float& hardPrice) const;

	const std::vector<DecalData>& GetDecals() const;

	void Upgrade(const std::string& upgradeId);
	bool IsFullyUpgraded(const std::string& upgradeId);

	void AddDecal(DecalData decalData);
	void SetDecal(const std::string& decalId);
	void SetDefaultDecal();
	DecalData GetDecal(const std::string& decalId) const;
	std::string GetActiveDecalId() const;
	float GetActiveDecalBonus() const;
	bool HasDecal(const std::string& decalId) const;

	void AddObserver(CarObserver* carObserver);

private:
	CarData m_carData;

	int m_speedUpgradeLevel;
	int m_accUpgradeLevel;
	int m_tiresUpgradeLevel;

	std::string m_activeDecalId;

	std::vector<DecalData> m_decals;

	std::vector<CarObserver*> m_observers;

	void NotifyUpgraded(const std::string& upgradeId);
	void NotifyChangedDecal(const std::string& decalId);
};

