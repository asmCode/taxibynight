#include "DummyAds.h"
#include "IAdsObserver.h"

DummyAds::DummyAds() :
	m_observer(NULL)
{
}

void DummyAds::LoadBannerAd()
{
}

void DummyAds::LoadInterstitialAd()
{
}

void DummyAds::ShowBannerAd(bool show)
{
}

void DummyAds::ShowInterstitialAd(bool show)
{
}

bool DummyAds::IsBannerAdReady() const
{
	return true;
}

bool DummyAds::IsInterstitialAdReady() const
{
	return true;
}

void DummyAds::AddObserver(IAdsObserver* observer)
{
}

