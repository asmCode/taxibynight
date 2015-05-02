#pragma once

#include <Analytics/AnalyticsEvent.h>

// Opuszczenie gry na ekranie podsumowania (obojetne czy po pauzie czy timeoucie)
class LeaveGame : public AnalyticsEvent
{
public:
	LeaveGame();
};

