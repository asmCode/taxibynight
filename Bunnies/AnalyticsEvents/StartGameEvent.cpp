#include "StartGameEvent.h"

StartGameEvent::StartGameEvent()
{
	AddEventParameter("majak", "smierdzi");
	AddEventParameter("dupa", "jasia");
}

std::string StartGameEvent::GetEventName() const
{
	return "StartGame";
}
