#ifndef BONUS
#define BONUS

#include "BonusType.h"
#include <Math/Matrix.h>
#include <Core/stdint.h>
#include <string>

class Bonus
{
public:
	Bonus(BonusType bonusType, float time);
	~Bonus();

	BonusType GetBonusType() const;
	std::string GetName() const;
	std::string GetIconName() const;
	float GetTimeLeft() const;
	void SetTimeLeft(float time);

	bool IsInstantBonus() const;
	bool IsRunDown() const;

	void DecreaseTimeLeft(float seconds);

private:
	BonusType m_bonusType;
	float m_timeLeft;
};

#endif // BONUS

