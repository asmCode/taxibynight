#pragma once

#include <string>

class PlayerObserver
{
public:
	~PlayerObserver() {}

	virtual void SoftMoneyChanged() {}
	virtual void HardMoneyChanged() {}
	virtual void ExperienceChanged() {}
	virtual void LevelChanged() {}
};

