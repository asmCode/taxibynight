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

void Cpp2Java::CallStaticMethodV(const std::string& methodName)
{
	JNIEnv* env;
	if (javaVM->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)
	{
		LOGE("CallStaticMethodV: cannot get env");
		return;
	}

	jclass clazz = env->FindClass("com/ssg/taxisoftlaunch/GL2JNILib");
	jmethodID methodId = env->GetStaticMethodID(clazz, methodName.c_str(), "()V");

	env->CallStaticVoidMethod(clazz, methodId);
}

