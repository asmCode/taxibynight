#pragma once

#include <jni.h>
#include <string>

class Cpp2Java
{
public:
	static void RequestAppQuit();
	static void LogAnalyticsEvent(const std::string& name);
	static void LogAnalyticsEvent(const std::string& name, const std::string& value);
	static void LogAnalyticsEvent(const std::string& name, float value);

private:
	static void CallStaticMethodV(const std::string& methodName);
	static void CallStaticMethodV(const std::string& methodName, const std::string& param);
	static void CallStaticMethodV(const std::string& methodName, const std::string& param1, const std::string& param2);
	static void CallStaticMethodV(const std::string& methodName, const std::string& param1, float param2);
};

