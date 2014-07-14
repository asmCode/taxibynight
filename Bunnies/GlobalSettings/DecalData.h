#pragma once

#include <string>

class DecalData
{
public:
	DecalData() :
		SoftPrice(0.0f),
		HardPrice(0.0f),
		Bonus(0.0f)
	{

	}

	std::string Id;
	float SoftPrice;
	float HardPrice;
	float Bonus;
};
