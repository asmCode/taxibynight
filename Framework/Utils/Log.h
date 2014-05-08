#pragma once

#include <string>
#include <fstream>

class Log
{
private:
	static std::stringstream logSStream;
	static std::ofstream m_fileStream;
	static char dstBuf[1024];
	static char timeBuff[80];
	
	static bool logThreadName;

	static void UpdateTime();
	static void UpdateLog();
		
public:
	static void StartLog(bool logThreadName);
	
	static void LogT(const char *formatString, ...);
};
