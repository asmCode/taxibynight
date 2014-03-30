#ifndef IADS
#define IADS

class IAdsObserver;

class IAds
{
public:
	virtual ~IAds() {}
	
	virtual void LoadBannerAd() = 0;
	virtual void LoadInterstitialAd() = 0;
	
	virtual void ShowBannerAd(bool show) = 0;
	virtual void ShowInterstitialAd(bool show) = 0;
	
	virtual bool IsBannerAdReady() const = 0;
	virtual bool IsInterstitialAdReady() const = 0;
	
	virtual void AddObserver(IAdsObserver* observer) = 0;
};

#endif // IADS

