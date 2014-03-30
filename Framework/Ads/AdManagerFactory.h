#ifndef AD_MANAGER_FACTORY
#define AD_MANAGER_FACTORY

class IAds;

class AdManagerFactory
{
public:
	static IAds* Create();
};

#endif // AD_MANAGER_FACTORY

