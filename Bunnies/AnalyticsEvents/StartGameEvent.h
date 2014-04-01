#ifndef START_GAME_EVENT
#define START_GAME_EVENT

#include <Analytics/AnalyticsEvent.h>

class StartGameEvent : public AnalyticsEvent
{
public:
	StartGameEvent();
	
	std::string GetEventName() const;
};

#endif // START_GAME_EVENT

