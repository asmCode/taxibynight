#ifdef _TIZEN

#include "../Path.h"
#include <Utils/StringUtils.h>
#include <FIo.h>

using namespace Tizen::Io;

bool Path::IsFileExists(const char *fileName)
{
	return File::IsFileExist(fileName);
}

void Path::GetAllFiles(std::vector<std::string> &files,
					   const std::string &path,
					   const std::string &filter)
{
	Directory* pDir = new Directory();
	DirEnumerator* pDirEnum;

	result r = pDir->Construct(path.c_str());
	if (r != E_SUCCESS)
	{
		AppLog(GetErrorMessage(r));
		delete pDir;
		return;
	}

    pDirEnum = pDir->ReadN();

	while (pDirEnum->MoveNext() == E_SUCCESS)
	{
		DirEntry entry = pDirEnum->GetCurrentDirEntry();

		if (entry.IsDirectory())
			continue;

		Path fileName(StringUtils::ToNarrow(entry.GetName().GetPointer()));

		if (fileName.GetExt() == filter.substr(filter.size() - 3))
		{
			files.push_back(fileName.GetFilenameExt());
		}
	}

	delete pDir;
	delete pDirEnum;
}

#endif
