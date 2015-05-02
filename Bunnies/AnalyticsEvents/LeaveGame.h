#pragma once

#include <Analytics/AnalyticsEvent.h>

// Opuszczenie gry (Pauza->End Round->Main Menu)
class LeaveGame : public AnalyticsEvent
{
public:
	LeaveGame();
};

