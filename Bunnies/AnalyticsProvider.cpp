#include "AnalyticsProvider.h"
#include <Analytics/FlurryAnalytics.h>

std::string AnalyticsProvider::FlurryApiKey = "VXW68K4STQYP5Z9SBQYN";
IAnalytics* AnalyticsProvider::m_analytics;

IAnalytics* AnalyticsProvider::GetAnalytics()
{
	if (m_analytics == NULL)
	{
		FlurryAnalytics* flurry = new FlurryAnalytics();
		flurry->Initialize(FlurryApiKey);
		
		m_analytics = flurry;
	}
	
	return m_analytics;
}
