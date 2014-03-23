#include "Log.h"
#include <sstream>
#include <time.h>
#include <stdarg.h>
#include <Windows.h>
#include <debugapi.h>

bool Log::logThreadName;

std::stringstream Log::logSStream;
char Log::dstBuf[1024];
char Log::timeBuff[80];

void Log::UpdateTime()
{
	time_t	rawTime;
	tm		*timeInfo;
	
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	
	strftime(timeBuff, 80, "%X", timeInfo);
}

void Log::UpdateLog()
{
	logSStream.str("");
	logSStream << "[";
	
	if (logThreadName)
	{		
		logSStream << "-";
	}
	
	logSStream << timeBuff << "-T    ] " << dstBuf << std::endl;
}

void Log::StartLog(bool logThreadName)
{
	Log::logThreadName = logThreadName;
}

void Log::LogT(const char *formatString, ...)
{	
	va_list argptr;
	va_start(argptr, formatString);
	vsprintf(dstBuf, formatString, argptr);
	va_end(argptr);
	
	UpdateTime();
	UpdateLog();
	
	OutputDebugStringA(logSStream.str().c_str());
}

