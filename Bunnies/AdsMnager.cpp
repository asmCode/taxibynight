#include "AdsMnager.h"
#include <Ads/AdManagerFactory.h>
#include <Ads/AdMobAds.h>
#include <Utils/Log.h>
#include <assert.h>

AdsManager* AdsManager::m_instance;
std::string AdsManager::AdMobBannerToken = "ca-app-pub-7651431092078292/6036357967";
std::string AdsManager::AdMobFullScreenToken = "ca-app-pub-7651431092078292/3932012763";

AdsManager* AdsManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new AdsManager();
	
	return m_instance;
}

AdsManager::AdsManager() :
	m_ads(NULL),
	m_bannerAdReady(false),
	m_fullScreenAdReady(false)
{
	
}

void AdsManager::LoadBannerAd()
{
	assert(m_ads != NULL);
	
	m_ads->LoadBannerAd();
}

void AdsManager::LoadFullScreenAd()
{
	assert(m_ads != NULL);
	
	m_ads->LoadInterstitialAd();
}

void AdsManager::ShowBannerAd(bool show)
{
	assert(m_ads != NULL);
	
	m_ads->ShowBannerAd(show);
}

void AdsManager::ShowFullScreenAd()
{
	assert(m_ads != NULL);
	
	m_fullScreenAdReady = false;
	
	m_ads->ShowInterstitialAd(true);
}

bool AdsManager::Initialize(IServiceProvider* serviceProvider)
{
	m_ads = AdManagerFactory::Create();
	
	bool result = ((AdMobAds*)m_ads)->Initialize(AdMobBannerToken, AdMobFullScreenToken, serviceProvider);
	if (!result)
		return false;
	
	m_ads->AddObserver(this);
		
	return true;
}

void AdsManager::BannerAdLoaded()
{
	Log::LogT("Banner ad loaded");
	
	m_bannerAdReady = true;
}

void AdsManager::FullScreenAdLoaded()
{
	Log::LogT("Full screen ad loaded");
	
	m_fullScreenAdReady = true;
}

void AdsManager::FullScreenAdClosed()
{
	Log::LogT("Full screen ad closed");
	
	LoadFullScreenAd();
}

