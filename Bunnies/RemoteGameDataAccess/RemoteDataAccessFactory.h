#ifndef REMOTE_DATA_ACCESS_FACTORY
#define REMOTE_DATA_ACCESS_FACTORY

class IRemoteGameDataAccess;

class RemoteDataAccessFactory
{
public:
	static IRemoteGameDataAccess* Create();
};

#endif // REMOTE_DATA_ACCESS_FACTORY
