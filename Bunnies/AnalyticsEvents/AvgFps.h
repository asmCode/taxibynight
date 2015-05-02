#pragma once

#include <Analytics/AnalyticsEvent.h>

class AvgFps : public AnalyticsEvent
{
public:
	AvgFps(int fps);
};

