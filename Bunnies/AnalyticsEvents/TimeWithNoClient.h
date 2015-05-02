#pragma once

#include <Analytics/AnalyticsEvent.h>

class TimeWithNoClient : public AnalyticsEvent
{
public:
	TimeWithNoClient(float value);
};

