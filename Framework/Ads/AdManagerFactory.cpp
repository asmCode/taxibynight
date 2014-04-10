#include "AdManagerFactory.h"

#include "IAds.h"

#if __APPLE__
#include "AdMobAds.h"

IAds* AdManagerFactory::Create()
{
	return new AdMobAds();
}

#else

#include "DummyAds.h"

IAds* AdManagerFactory::Create()
{
	return new DummyAds();
}

#endif

