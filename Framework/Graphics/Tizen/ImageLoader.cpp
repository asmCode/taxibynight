#ifdef _TIZEN

#include "../ImageLoader.h"
#include <Utils/StringUtils.h>
#include <IO/Path.h>
#include <FMedia.h>
#include <FBase.h>
#include <stdio.h>
#include <memory.h>
#include <stddef.h>
#include <assert.h>

using namespace Tizen::Base;
using namespace Tizen::Graphics;

bool ImageLoader::LoadFromFile(const std::string &path,
							     uint8_t *&data,
								 uint32_t &width,
								 uint32_t &height,
								 uint32_t &bytesCount)
{
	assert(!path.empty());
	if (path.empty())
		return false;

	Path filePath(path);
	if (StringUtils::LowerCase(filePath.GetExt()) != "png" &&
		StringUtils::LowerCase(filePath.GetExt()) != "jpg")
		return false;

	Tizen::Media::Image image;
	image.Construct();

	Bitmap *bitmap = image.DecodeN(path.c_str(), BITMAP_PIXEL_FORMAT_R8G8B8A8);
	if (bitmap == null)
	{
		AppLogException("Couldn't load image");
		return false;
	}

	int w, h;

	ByteBuffer *buffer = image.DecodeToBufferN(path.c_str(), BITMAP_PIXEL_FORMAT_R8G8B8A8, w, h);

	width = w;
	height = h;
	bytesCount = 4;

	data = new uint8_t[width * height * bytesCount];

	memcpy(data, buffer->GetPointer(), width * height * bytesCount);

	delete buffer;
	delete bitmap;

	return true;
}

#endif
