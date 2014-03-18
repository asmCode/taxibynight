#include "../ImageLoader.h"
#include "Utils/StringUtils.h"
#include <IO/Path.h>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

bool ImageLoader::LoadFromFile(const std::string &path,
							   uint8_t *&imgData,
							   uint32_t &width,
							   uint32_t &height,
							   uint32_t &bytesCount)
{
	NSString *strFilename = [NSString stringWithUTF8String:path.c_str()];
	if (strFilename == NULL)
		return false;
	
	UIImage *uiImage = [[UIImage alloc] initWithContentsOfFile:strFilename];
	if (uiImage == NULL)
		return false;
	
	CGImage *cgImage = uiImage.CGImage;
	
	CGDataProvider *dataProvider = CGImageGetDataProvider(cgImage);
	if (dataProvider == NULL)
		return false;
	
	CFDataRef data = CGDataProviderCopyData(dataProvider);
	if (data == NULL)
		return false;
	
	width = static_cast<uint32_t>(CGImageGetWidth(cgImage));
	height = static_cast<uint32_t>(CGImageGetHeight(cgImage));
	bytesCount = static_cast<uint32_t>(CGImageGetBitsPerPixel(cgImage)) / 8;
	imgData = new uint8_t[CGImageGetBytesPerRow(cgImage) * height];
	if (imgData == NULL)
		return false;
	
	CFDataGetBytes(data, CFRangeMake(0, CFDataGetLength(data)), imgData);
	
	CFRelease(data);

	return true;
}

