#pragma once

#include <string>

class Car;

class CarObserver
{
public:
	virtual void Upgraded(Car* car, const std::string& upgradeId) {}
	virtual void ChangedDecal(Car* car, const std::string& decalId) {}
};

