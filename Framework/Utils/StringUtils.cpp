#include "StringUtils.h"
#include <stdio.h>
#include <algorithm>
#include <ctype.h>

#if 0 // tizen crap
#include <FBase.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Utility;
#endif

std::string StringUtils::UpperCase(const std::string &str)
{
	std::string result;
	result.resize(str.length());
	std::transform(str.begin(), str.end(), result.begin(), toupper);
	return result;
}

std::string StringUtils::LowerCase(const std::string &str)
{
	std::string result;
	result.resize(str.length());
	std::transform(str.begin(), str.end(), result.begin(), tolower);
	return result;
}

std::wstring StringUtils::ToWide(const std::string &str)
{
	return std::wstring(str.begin(), str.end());
}

std::string StringUtils::ToNarrow(const std::wstring &str)
{
	return std::string(str.begin(), str.end());
}

std::string StringUtils::ToString(float val)
{
	char txt[128];
	sprintf(txt, "%.2f", val);
	return txt;
}

std::string StringUtils::ToString(int val)
{
	char txt[128];
	sprintf(txt, "%d", val);
	return txt;
}

void StringUtils::Split(const std::string src, const std::string &separator, std::vector<std::string> &result)
{
	result.clear();

	std::string _src = src;
	int offset = 0;

	while (offset != -1)
	{
		offset = _src.find_first_of(separator);
		if (offset != -1)
		{
			result.push_back(_src.substr(0, offset));
			_src = _src.substr(offset + separator.length());
		}
	}

	result.push_back(_src);
}

std::string StringUtils::ToBase64(const std::string& str)
{
	return str;
	/*
	ByteBuffer buffer;
	buffer.Construct(reinterpret_cast<const byte*>(str.c_str()), 0, str.size(), str.size());
	String base64String;
	StringUtil::EncodeToBase64String(buffer, base64String);

	return StringUtils::ToNarrow(base64String.GetPointer());
	*/
}

std::string StringUtils::FromBase64(const std::string& base64)
{
	return base64;

	/*
	std::string str;
	ByteBuffer *buffer = StringUtil::DecodeBase64StringN(base64.c_str());
	if (buffer != NULL)
		str.assign(reinterpret_cast<const char*>(buffer->GetPointer()), buffer->GetCapacity());

	return str;
	*/
}
