#ifdef __ANDROID__

#include "../Path.h"
#include <dirent.h>

// TODO: dokonczyc implementacje!!

bool Path::IsFileExists(const char *fileName)
{
	return false;
}

void Path::GetAllFiles(std::vector<std::string> &files,
					   const std::string &path,
					   const std::string &filter)
{
	dirent** filenames;
	int count = scandir(path.c_str(), &filenames, NULL, alphasort);

	for (int i = 0; i < count; i++)
		files.push_back(filenames[i]->d_name);
}

#endif
