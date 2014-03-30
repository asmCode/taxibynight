#ifndef ADMOB_ADS
#define ADMOB_ADS

#include "IAds.h"
#include <string>

class GADBannerViewImpl;
class GADFullScreenAdImpl;
class GADBannerViewObserverImpl;
class IServiceProvider;

class AdMobAds : public IAds
{
public:
	AdMobAds();
	
	bool Initialize(const std::string& bannerAdId,
					const std::string& fullScreenAdId,
					IServiceProvider* serviceProvider);
	
	void LoadBannerAd();
	void LoadInterstitialAd();
	
	void ShowBannerAd(bool show);
	void ShowInterstitialAd(bool show);
	
	bool IsBannerAdReady() const;
	bool IsInterstitialAdReady() const;
	
	void AddObserver(IAdsObserver* observer);
	
private:
	IAdsObserver* m_observer;
	
	IServiceProvider* m_serviceProvider;
	
	std::string m_fullScreenAdId;
	
	GADBannerViewImpl *m_bannerView; // PIMPL
	GADBannerViewObserverImpl *m_bannerViewObserver; // PIMPL
	GADFullScreenAdImpl *m_fullScreenAd;
};

#endif // ADMOB_ADS

