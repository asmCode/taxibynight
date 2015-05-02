#pragma once

#include <Analytics/AnalyticsEvent.h>

// Restart gry (Pauza->End Round->Again)
class Restart : public AnalyticsEvent
{
public:
	Restart();
};

