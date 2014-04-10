#ifndef DUMMY_ADS
#define DUMMY_ADS

#include "IAds.h"
#include <string>

class DummyAds : public IAds
{
public:
	DummyAds();
	
	void LoadBannerAd();
	void LoadInterstitialAd();
	
	void ShowBannerAd(bool show);
	void ShowInterstitialAd(bool show);
	
	bool IsBannerAdReady() const;
	bool IsInterstitialAdReady() const;
	
	void AddObserver(IAdsObserver* observer);
	
private:
	IAdsObserver* m_observer;
};

#endif // DUMMY_ADS

