#include "Cpp2Java.h"
#include <android/log.h>

#define  LOG_TAG    "taxi"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern JavaVM *javaVM;

void Cpp2Java::RequestAppQuit()
{
	CallStaticMethodV("RequestAppClose");
}

void Cpp2Java::LogAnalyticsEvent(const std::string& name)
{
	CallStaticMethodV("LogAnalyticsEvent", name);
}

void Cpp2Java::LogAnalyticsEvent(const std::string& name, const std::string& value)
{
	CallStaticMethodV("LogAnalyticsEvent", name, value);
}

void Cpp2Java::LogAnalyticsEvent(const std::string& name, float value)
{
	CallStaticMethodV("LogAnalyticsEvent", name, value);
}

void Cpp2Java::CallStaticMethodV(const std::string& methodName)
{
	JNIEnv* env;
	if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("CallStaticMethodV: cannot get env");
		return;
	}

	jclass clazz = env->FindClass("com/semiseriousgames/taxibynight/GL2JNILib");
	jmethodID methodId = env->GetStaticMethodID(clazz, methodName.c_str(), "()V");

	env->CallStaticVoidMethod(clazz, methodId);
}

void Cpp2Java::CallStaticMethodV(const std::string& methodName, const std::string& param)
{
	JNIEnv* env;
	if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("CallStaticMethodV: cannot get env");
		return;
	}

	jclass clazz = env->FindClass("com/semiseriousgames/taxibynight/GL2JNILib");
	jmethodID methodId = env->GetStaticMethodID(clazz, methodName.c_str(), "(Ljava/lang/String;)V");

	jstring javaParam = env->NewStringUTF(param.c_str());

	env->CallStaticVoidMethod(clazz, methodId, javaParam);
}

void Cpp2Java::CallStaticMethodV(const std::string& methodName, const std::string& param1, const std::string& param2)
{
	JNIEnv* env;
	if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("CallStaticMethodV: cannot get env");
		return;
	}

	jclass clazz = env->FindClass("com/semiseriousgames/taxibynight/GL2JNILib");
	jmethodID methodId = env->GetStaticMethodID(clazz, methodName.c_str(), "(Ljava/lang/String;Ljava/lang/String;)V");

	jstring javaParam1 = env->NewStringUTF(param1.c_str());
	jstring javaParam2 = env->NewStringUTF(param2.c_str());

	env->CallStaticVoidMethod(clazz, methodId, javaParam1, javaParam2);
}

void Cpp2Java::CallStaticMethodV(const std::string& methodName, const std::string& param1, float param2)
{
	JNIEnv* env;
	if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("CallStaticMethodV: cannot get env");
		return;
	}

	jclass clazz = env->FindClass("com/semiseriousgames/taxibynight/GL2JNILib");
	jmethodID methodId = env->GetStaticMethodID(clazz, methodName.c_str(), "(Ljava/lang/String;F)V");

	jstring javaParam1 = env->NewStringUTF(param1.c_str());

	env->CallStaticVoidMethod(clazz, methodId, javaParam1, param2);
}

