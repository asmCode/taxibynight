#pragma once

#include "UpgradeId.h"
#include "GlobalSettings/CarData.h"
#include <string>
#include <vector>

class Car
{
public:
	Car();

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

private:
	CarData m_carData;

	int m_speedUpgradeLevel;
	int m_accUpgradeLevel;
	int m_tiresUpgradeLevel;

	int GetUpgradeLevel(const std::string& id);
};

