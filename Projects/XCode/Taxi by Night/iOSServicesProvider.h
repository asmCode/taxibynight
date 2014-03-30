#ifndef IOS_SERVICES_PROVIDER
#define IOS_SERVICES_PROVIDER

#include <System/IServiceProvider.h>
#include <UIKit/UIView.h>
#include <UIKit/UIViewController.h>

class iOSServicesProvider : public IServiceProvider
{
public:
	iOSServicesProvider(UIViewController* viewController);
	
	void* GetService(const std::string& serviceName);
	
private:
	UIViewController* m_viewController;
};

#endif // IOS_SERVICES_PROVIDER

