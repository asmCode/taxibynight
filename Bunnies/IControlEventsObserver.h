#ifndef ICONTROL_EVENTS_OBSERVER
#define ICONTROL_EVENTS_OBSERVER

#include <stdint.h>

class Control;

class IControlEventsObserver
{
public:
	virtual void Clicked(Control *control, uint32_t x, uint32_t y) {};
};

#endif // ICONTROL_EVENTS_OBSERVER

