#ifdef __ANDROID__

#include "../Path.h"
#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>

// TODO: dokonczyc implementacje!!

std::string extFilter;

int selectgrf(const struct dirent *namelist)
{
   int r = fnmatch(extFilter.c_str(), namelist->d_name, FNM_PERIOD);

   return (r==0)?1:0;
}

bool Path::IsFileExists(const char *fileName)
{
	struct stat buffer;
	return (stat(fileName, &buffer) == 0);
}

void Path::GetAllFiles(std::vector<std::string> &files,
					   const std::string &path,
					   const std::string &filter)
{
	extFilter = filter;

	dirent** filenames;
	int count = scandir(path.c_str(), &filenames, selectgrf, alphasort);

	for (int i = 0; i < count; i++)
		files.push_back(filenames[i]->d_name);
}

#endif
