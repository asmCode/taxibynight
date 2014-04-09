#include "RemoteDataAccessFactory.h"
#include "ParseGameDataAccess.h"

IRemoteGameDataAccess* RemoteDataAccessFactory::Create()
{
	return new ParseGameDataAccess();
}
