#ifdef __ANDROID__

#include "../ImageLoader.h"
#include "Utils/StringUtils.h"
#include <IO/Path.h>
#include <LodePNG/lodepng.h>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

bool ImageLoader::LoadFromFile(const std::string &path,
							     uint8_t *&data,
								 uint32_t &width,
								 uint32_t &height,
								 uint32_t &bytesCount)
{
	int result = lodepng_decode32_file(&data, &width, &height, path.c_str());
	bytesCount = 4;
	
	return result == 0;
}

#endif

