#include "iOSServicesProvider.h"
#include <assert.h>

iOSServicesProvider::iOSServicesProvider(UIViewController* viewController)
{
	m_viewController = viewController;
}

void* iOSServicesProvider::GetService(const std::string& serviceName)
{
	if (serviceName == "ViewController")
		return (__bridge_retained void *)m_viewController;
	
	assert(false);
	
	return NULL;
}
