#pragma once

#include <jni.h>
#include <string>

class Cpp2Java
{
public:
	static void RequestAppQuit();

private:
	/*static JNIEnv* m_env;
	static jclass m_clazz;
	static jmethodID m_requestAppQuitId;*/

	static void CallStaticMethodV(const std::string& methodName);
};

