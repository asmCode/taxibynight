#include "../Log.h"
#include <android/log.h>
#include <sstream>
#include <time.h>
#include <stdarg.h>

#define  LOG_TAG    "taxi"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

bool Log::logThreadName;

std::stringstream Log::logSStream;
std::ofstream Log::m_fileStream;
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
	m_fileStream.open("log.txt");

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

	LOGI("%s", logSStream.str().c_str());

	m_fileStream.write(logSStream.str().c_str(), logSStream.str().length());
	m_fileStream.flush();
}

