#include "AdsMnager.h"
#include <Ads/AdManagerFactory.h>
#include <Ads/AdMobAds.h>

AdsManager* AdsManager::m_instance;
std::string AdsManager::AdMobBannerToken = "ca-app-pub-7651431092078292/6036357967";
std::string AdsManager::AdMobFullScreenToken = "ca-app-pub-7651431092078292/6036357967";

AdsManager* AdsManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new AdsManager();
	
	return m_instance;
}

AdsManager::AdsManager() :
	m_ads(NULL)
{
	
}

bool AdsManager::Initialize(IServiceProvider* serviceProvider)
{
	m_ads = AdManagerFactory::Create();
	
	return ((AdMobAds*)m_ads)->Initialize(AdMobBannerToken, AdMobFullScreenToken, serviceProvider);
}

void AdsManager::BannerAdLoaded()
{
	
}

void AdsManager::FullScreenAdLoaded()
{
	
}

void AdsManager::FullScreenAdClosed()
{
	
}

