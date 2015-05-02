#pragma once

#include <Analytics/AnalyticsEvent.h>

// Ponowna gra po timeoucie (Pauza->End Round->Main Menu)
class PlayAgainAfterTimeout : public AnalyticsEvent
{
public:
	PlayAgainAfterTimeout();
};

