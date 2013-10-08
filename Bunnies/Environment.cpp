#include "Environment.h"

Environment *GenericSingleton<Environment>::instance;

Environment::Environment()
{
	m_screenWidth = 0;
	m_screenHeight = 0;
}

void Environment::SetScreenSize(unsigned width, unsigned height)
{
	this->m_screenWidth = width;
	this->m_screenHeight = height;
}

void Environment::SetIOSVersion(const std::string &iosVersion)
{
	this->m_iosVersion = iosVersion;
}

void Environment::SetBasePath(const std::string &basePath)
{
	this->m_basePath = basePath;
}

unsigned Environment::GetScreenWidth() const
{
	return m_screenWidth;
}

unsigned Environment::GetScreenHeight() const
{
	return m_screenHeight;
}

std::string Environment::GetIOSVersion() const
{
	return m_iosVersion;
}

std::string Environment::GetBasePath() const
{
	return m_basePath;
}

