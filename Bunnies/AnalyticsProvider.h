#ifndef ANALYTICS_PROVIDER
#define ANALYTICS_PROVIDER

#include <Analytics/IAnalytics.h>
#include <string>

class AnalyticsProvider
{
public:
	static IAnalytics* GetAnalytics();
	
private:
	static IAnalytics* m_analytics;
};

#endif // ANALYTICS_PROVIDER

