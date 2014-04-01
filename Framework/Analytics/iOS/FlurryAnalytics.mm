#include "../FlurryAnalytics.h"
#include "AnalyticsEvent.h"
#import "Flurry.h"

void FlurryAnalytics::Initialize(const std::string& apiKey)
{
	[Flurry setCrashReportingEnabled:YES];
	[Flurry startSession:[NSString stringWithUTF8String:apiKey.c_str()]];
}

void FlurryAnalytics::SetUser(const std::string& userId)
{
}

void FlurryAnalytics::TrackEvent(const AnalyticsEvent& event)
{
	NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
	
	for (int i = 0; i < event.GetParametersCount(); i++)
	{
		NSString *nsName = [NSString stringWithUTF8String:event.GetParameterName(i).c_str()];
		NSString *nsValue = [NSString stringWithUTF8String:event.GetParameterValue(i).c_str()];
		
		[params setObject:nsValue forKey:nsName];
	}
	
	NSString *nsEventName = [NSString stringWithUTF8String:event.GetEventName().c_str()];
	
	[Flurry logEvent:nsEventName withParameters:params];
}

