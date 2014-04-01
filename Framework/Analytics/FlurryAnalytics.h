#ifndef FLURRY_ANALYTICS
#define FLURRY_ANALYTICS

#include "IAnalytics.h"

class FlurryAnalytics : public IAnalytics
{
public:
	void SetUser(const std::string& userId);
	void TrackEvent(const AnalyticsEvent& event);
};

#endif // FLURRY_ANALYTICS

