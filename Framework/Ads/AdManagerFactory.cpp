#include "AdManagerFactory.h"

#include "IAds.h"
#include "AdMobAds.h"

IAds* AdManagerFactory::Create()
{
	return new AdMobAds();
}
