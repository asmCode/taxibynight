#pragma once

#include <Analytics/IAnalytics.h>

class AnalyticsFactory
{
public:
	static IAnalytics* Create();
};

