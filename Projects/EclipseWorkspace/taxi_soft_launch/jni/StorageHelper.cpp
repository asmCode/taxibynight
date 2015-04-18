#include "StorageHelper.h"
#include <android/asset_manager.h>
#include <fstream>

std::string StorageHelper::UnpackAsset(
		AAssetManager* assetManager,
		const std::string& assetPath,
		const std::string& writablePath)
{
	AAsset* asset = AAssetManager_open(assetManager, assetPath.c_str(), AASSET_MODE_UNKNOWN);
	if (NULL == asset)
	{
		return "";
	}

	long size = AAsset_getLength(asset);
	char* buffer = new char[size];
	AAsset_read (asset, buffer, size);
	AAsset_close(asset);

	std::ofstream tmpFile((writablePath + "/tmp").c_str(), std::ios::binary);
	tmpFile.write(buffer, size);
	tmpFile.close();

	delete[] buffer;

	return writablePath + "/tmp";
}

void StorageHelper::DeleteUnpackedAsset(std::string unpackedAssetPath)
{

}

