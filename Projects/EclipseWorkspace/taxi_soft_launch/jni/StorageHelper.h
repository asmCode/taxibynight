#include <string>

class AAssetManager;

class StorageHelper
{
public:
	static std::string UnpackAsset(
		AAssetManager* assetManager,
		const std::string& assetPath,
		const std::string& writablePath);

	static void DeleteUnpackedAsset(std::string unpackedAssetPath);
};

