#pragma once

#include <Analytics/AnalyticsEvent.h>

class EarnedMoney : public AnalyticsEvent
{
public:
	EarnedMoney(float value);
};

