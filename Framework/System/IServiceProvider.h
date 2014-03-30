#ifndef ISERVICE_PROVIDER
#define ISERVICE_PROVIDER

#include <string>

class IServiceProvider
{
public:
	virtual void* GetService(const std::string& serviceName) = 0;
};

#endif // ISERVICE_PROVIDER

