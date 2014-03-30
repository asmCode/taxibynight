#ifndef ADMOB_ADS
#define ADMOB_ADS

#include "IAds.h"
#include <string>

class GADBannerViewImpl;
class IServiceProvider;

class AdMobAds : public IAds
{
public:
	AdMobAds();
	
	bool Initialize(const std::string& bannerAdId,
					const std::string& fullScfeenAdId,
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
	
	GADBannerViewImpl *m_bannerView; // PIMPL
};

#endif // ADMOB_ADS

