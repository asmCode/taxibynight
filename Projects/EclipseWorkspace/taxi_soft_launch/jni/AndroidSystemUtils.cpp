#include "AndroidSystemUtils.h"
#include "Cpp2Java.h"
#include <Utils/Log.h>

void AndroidSystemUtils::QuitApplication()
{
	Cpp2Java::RequestAppQuit();
}

