#ifndef _ISCREEN_
#define _ISCREEN_

#include <UI/IGestureHandler.h>

class IScreen : public IGestureHandler
{
public:
	virtual bool InitResources() = 0;
	virtual bool ReleaseResources() = 0;

	virtual void Draw(float time, float seconds) = 0;
	virtual void Update(float time, float seconds) = 0;
};

#endif // _ISCREEN_

