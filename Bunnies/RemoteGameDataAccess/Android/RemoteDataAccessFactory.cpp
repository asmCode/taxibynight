#include "../RemoteDataAccessFactory.h"
#include "../DummyGameDataAccess.h"

IRemoteGameDataAccess* RemoteDataAccessFactory::Create()
{
	return new DummyGameDataAccess();
}
