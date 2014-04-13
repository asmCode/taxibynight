#ifndef BONUSES_MANAGER_OBSERVER
#define BONUSES_MANAGER_OBSERVER

#include "BonusType.h"

class IBonusesManagerObserver
{
public:
	virtual ~IBonusesManagerObserver() {}

	virtual void BonusActivated(BonusType bonusType) {}
	virtual void BonusDeactivated(BonusType bonusType) {}
};

#endif // BONUSES_MANAGER_OBSERVER

