#include "AnalyticsFactory.h"

#ifdef _WIN32

#include "DummyAnalytics.h"
IAnalytics* AnalyticsFactory::Create()
{
	return new DummyAnalytics();
}

#elif __APPLE__

#include <Analytics/FlurryAnalytics.h>
IAnalytics* AnalyticsFactory::Create()
{
	static const FlurryApiKey = "VXW68K4STQYP5Z9SBQYN";

	FlurryAnalytics* flurry = new FlurryAnalytics();
	flurry->Initialize(FlurryApiKey);

	return m_analytics;
}

#elif __ANDROID__

#include <Analytics/AnalyticsForAndroid.h>
IAnalytics* AnalyticsFactory::Create()
{
	return new AnalyticsForAndroid();
}

#endif

