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

	void GetUpgradeSlots(const std::string& id, int& totalSlots, int& activeSlots) const;
	void GetNextUpgradePrice(const std::string& id, float& softPrice, float& hardPrice);

	void AddObserver(CarObserver* carObserver);

private:
	CarData m_carData;

	int m_speedUpgradeLevel;
	int m_accUpgradeLevel;
	int m_tiresUpgradeLevel;

	std::vector<DecalData> m_decals;

	std::vector<CarObserver*> m_observers;

	int GetUpgradeLevel(const std::string& id);
};

