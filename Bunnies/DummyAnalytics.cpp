#include "DummyAnalytics.h"
#include <Analytics/AnalyticsEvent.h>
#include <Utils/Log.h>

void DummyAnalytics::SetUser(const std::string& userId)
{
}

void DummyAnalytics::TrackEvent(const AnalyticsEvent& event)
{
	switch (event.GetParamType())
	{
	case AnalyticsEvent::ParamType_None:
		Log::LogT("Logging event %s", event.GetEventName().c_str());
		break;

	case AnalyticsEvent::ParamType_String:
		Log::LogT("Logging event %s with param %s", event.GetEventName().c_str(), event.GetParamString().c_str());
		break;

	case AnalyticsEvent::ParamType_Float:
		Log::LogT("Logging event %s with param %f", event.GetEventName().c_str(), event.GetParamFloat());
		break;
	}
}

