#include "AdMobAds.h"
#include "IAdsObserver.h"
#import "GADBannerView.h"
#include "../../System/IServiceProvider.h"

class GADBannerViewImpl
{
public:
	GADBannerView* impl;
};

AdMobAds::AdMobAds() :
	m_observer(NULL),
	m_bannerView(NULL)
{
}

bool AdMobAds::Initialize(const std::string& bannerAdId,
						  const std::string& fullScfeenAdId,
						  IServiceProvider* serviceProvider)
{
	assert(serviceProvider != NULL);
	
	m_bannerView = new GADBannerViewImpl();
	m_bannerView->impl = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerLandscape];
	m_bannerView->impl.adUnitID = [NSString stringWithUTF8String:bannerAdId.c_str()];
	
	GADRequest *request = [GADRequest request];
	
	// Make the request for a test ad. Put in an identifier for
	// the simulator as well as any devices you want to receive test ads.
	request.testDevices = [NSArray arrayWithObjects:
						   GAD_SIMULATOR_ID,
                           nil];
	
	UIViewController* viewController = (__bridge_transfer UIViewController*)serviceProvider->GetService("ViewController");
	
	m_bannerView->impl.rootViewController = viewController;
	[[viewController view] addSubview:m_bannerView->impl];
	
	[m_bannerView->impl loadRequest:request];
	
	return true;
}

void AdMobAds::LoadBannerAd()
{
	
}

void AdMobAds::LoadInterstitialAd()
{
	
}

void AdMobAds::ShowBannerAd(bool show)
{
	
}

void AdMobAds::ShowInterstitialAd(bool show)
{
	
}

bool AdMobAds::IsBannerAdReady() const
{
	return true;
}

bool AdMobAds::IsInterstitialAdReady() const
{
	return true;
}

void AdMobAds::AddObserver(IAdsObserver* observer)
{
	m_observer = observer;
}

