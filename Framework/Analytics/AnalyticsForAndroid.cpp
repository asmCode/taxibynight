#include "AnalyticsForAndroid.h"
#include "AnalyticsEvent.h"

#ifdef __ANDROID__

#include "../../../Cpp2Java.h"

void AnalyticsForAndroid::SetUser(const std::string& userId)
{
}

void AnalyticsForAndroid::TrackEvent(const AnalyticsEvent& event)
{
	switch (event.GetParamType())
	{
	case AnalyticsEvent::ParamType_None:
		Cpp2Java::LogAnalyticsEvent(event.GetEventName());
		break;

	case AnalyticsEvent::ParamType_String:
		Cpp2Java::LogAnalyticsEvent(event.GetEventName(), event.GetParamString());
		break;

	case AnalyticsEvent::ParamType_Float:
		Cpp2Java::LogAnalyticsEvent(event.GetEventName(), event.GetParamFloat());
		break;

	case AnalyticsEvent::ParamType_Custom: // nie obsluguje
		break;
	}
}

#endif

