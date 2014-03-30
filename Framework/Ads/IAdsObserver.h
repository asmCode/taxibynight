#ifndef IADS_OBSERVER
#define IADS_OBSERVER

class IAdsObserver
{
public:
	virtual void BannerAdLoaded() {};
	virtual void FullScreenAdLoaded() {};
	virtual void FullScreenAdClosed() {};
};

#endif // IADS_OBSERVER

