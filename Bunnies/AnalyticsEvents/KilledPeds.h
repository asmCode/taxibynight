#pragma once

#include <Analytics/AnalyticsEvent.h>

class KilledPeds : public AnalyticsEvent
{
public:
	KilledPeds(int count);
};

