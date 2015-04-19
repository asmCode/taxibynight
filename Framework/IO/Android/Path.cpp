#ifdef __ANDROID__

#include "../Path.h"

bool Path::IsFileExists(const char *fileName)
{
	return false;
}

void Path::GetAllFiles(std::vector<std::string> &files,
					   const std::string &path,
					   const std::string &filter)
{
}

#endif
