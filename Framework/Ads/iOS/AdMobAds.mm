#include "AdMobAds.h"
#include "IAdsObserver.h"
#import "GADBannerView.h"
#import "GADInterstitial.h"
#include "../../System/IServiceProvider.h"

@interface GADBannerViewObserver : NSObject <GADBannerViewDelegate, GADInterstitialDelegate>
{
	IAdsObserver *m_observer;
}
@end

@implementation GADBannerViewObserver

- (id)initWithObserver:(IAdsObserver*)observer
{
	if ((self = [super init]))
		m_observer = observer;
	
	return self;
}

- (void)adViewDidReceiveAd:(GADBannerView *)bannerView
{
	if (m_observer != NULL)
		m_observer->BannerAdLoaded();
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)interstitial
{
	if (m_observer != NULL)
		m_observer->FullScreenAdLoaded();
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)interstitial
{
	if (m_observer != NULL)
		m_observer->FullScreenAdClosed();
}

@end

class GADBannerViewImpl
{
public:
	GADBannerView* impl;
};

class GADBannerViewObserverImpl
{
public:
	GADBannerViewObserver* impl;
};

class GADFullScreenAdImpl
{
public:
	GADInterstitial* m_impl;
};

AdMobAds::AdMobAds() :
	m_observer(NULL),
	m_bannerView(NULL),
	m_fullScreenAd(NULL)
{
}

bool AdMobAds::Initialize(const std::string& bannerAdId,
						  const std::string& fullScreenAdId,
						  IServiceProvider* serviceProvider)
{
	assert(serviceProvider != NULL);
	
	m_serviceProvider = serviceProvider;
	
	m_fullScreenAdId = fullScreenAdId;
	
	m_bannerView = new GADBannerViewImpl();
	m_bannerView->impl = [[GADBannerView alloc] initWithAdSize:kGADAdSizeSmartBannerLandscape];
	m_bannerView->impl.adUnitID = [NSString stringWithUTF8String:bannerAdId.c_str()];
	
	ShowBannerAd(false);
	
	GADRequest *request = [GADRequest request];
	
	// Make the request for a test ad. Put in an identifier for
	// the simulator as well as any devices you want to receive test ads.
	request.testDevices = [NSArray arrayWithObjects:
						   GAD_SIMULATOR_ID,
                           nil];
	
	UIViewController* viewController = (__bridge_transfer UIViewController*)serviceProvider->GetService("ViewController");
	
	m_bannerView->impl.rootViewController = viewController;
	[[viewController view] addSubview:m_bannerView->impl];
	
	return true;
}

void AdMobAds::LoadBannerAd()
{
	[m_bannerView->impl loadRequest:[GADRequest request]];
}

void AdMobAds::LoadInterstitialAd()
{
	if (m_fullScreenAd != NULL)
	{
		m_fullScreenAd->m_impl.delegate = nil;
		delete m_fullScreenAd;
	}
	
	m_fullScreenAd = new GADFullScreenAdImpl();
	m_fullScreenAd->m_impl = [[GADInterstitial alloc] init];
	m_fullScreenAd->m_impl.adUnitID = [NSString stringWithUTF8String:m_fullScreenAdId.c_str()];
	
	[m_fullScreenAd->m_impl setDelegate:m_bannerViewObserver->impl];
	[m_fullScreenAd->m_impl loadRequest:[GADRequest request]];
}

void AdMobAds::ShowBannerAd(bool show)
{
	assert(m_bannerView != NULL);
	assert(m_bannerView->impl != nil);
	
	if (m_bannerView == NULL &&
		m_bannerView->impl == nil)
		return;
	
	[m_bannerView->impl setHidden:!show];
}

void AdMobAds::ShowInterstitialAd(bool show)
{
	assert(m_fullScreenAd != NULL);
	assert(m_fullScreenAd->m_impl != nil);
	
	if (m_fullScreenAd == NULL &&
		m_fullScreenAd->m_impl == nil)
		return;
	
	UIViewController* viewController = (__bridge_transfer UIViewController*)m_serviceProvider->GetService("ViewController");
	assert(viewController != NULL);
	
	[m_fullScreenAd->m_impl presentFromRootViewController:viewController];
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
	
	m_bannerViewObserver = new GADBannerViewObserverImpl();
	m_bannerViewObserver->impl = [[GADBannerViewObserver alloc] initWithObserver:observer];
	
	[m_bannerView->impl setDelegate:m_bannerViewObserver->impl];
}

