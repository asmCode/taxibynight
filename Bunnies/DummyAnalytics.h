#ifndef DUMMY_ANALYTICS
#define DUMMY_ANALYTICS

#include <Analytics/IAnalytics.h>

class DummyAnalytics : public IAnalytics
{
public:
	void SetUser(const std::string& userId);
	void TrackEvent(const AnalyticsEvent& event);
};

#endif // DUMMY_ANALYTICS

