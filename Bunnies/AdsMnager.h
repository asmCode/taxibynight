#ifndef ADS_MANAGER
#define ADS_MANAGER

#include <Ads/IAdsObserver.h>
#include <string>

class IAds;
class IServiceProvider;

class AdsManager : public IAdsObserver
{
public:
	static AdsManager* GetInstance();
	
	bool Initialize(IServiceProvider* serviceProvider);
	
private:
	static std::string AdMobBannerToken;
	static std::string AdMobFullScreenToken;
	
	static AdsManager* m_instance;
	
	IAds* m_ads;
	
	AdsManager();

	// IAdsObserver implementation
	void BannerAdLoaded();
	void FullScreenAdLoaded();
	void FullScreenAdClosed();
};

#endif // ADS_MANAGER