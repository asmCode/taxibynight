#ifdef __ANDROID__

#include "../ImageLoader.h"
#include "Utils/StringUtils.h"
#include <IO/Path.h>
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
	width = 64;
	height = 64;
	bytesCount = 4;
	
	data = new uint8_t[width * height * bytesCount];
	
	return true;
}

#endif

