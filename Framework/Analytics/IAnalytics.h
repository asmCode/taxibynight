#ifndef IANALYTICS
#define IANALYTICS

#include <string>

class AnalyticsEvent;

class IAnalytics
{
public:
	virtual void SetUser(const std::string& userId) = 0;
	virtual void TrackEvent(const AnalyticsEvent& event) = 0;
};

#endif // IANALYTICS

