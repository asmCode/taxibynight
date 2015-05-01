#include "AnalyticsProvider.h"
#include "AnalyticsFactory.h"

IAnalytics* AnalyticsProvider::m_analytics;

IAnalytics* AnalyticsProvider::GetAnalytics()
{
	if (m_analytics == NULL)
	{
		m_analytics = AnalyticsFactory::Create();
	}

	return m_analytics;
}
