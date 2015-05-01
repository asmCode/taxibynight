#pragma once

#include "IAnalytics.h"

class AnalyticsForAndroid : public IAnalytics
{
public:
	void SetUser(const std::string& userId);
	void TrackEvent(const AnalyticsEvent& event);
};

