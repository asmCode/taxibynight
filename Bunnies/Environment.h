#ifndef SSG_ENVIRONMENT_H
#define SSG_ENVIRONMENT_H

#include <Core/GenericSingleton.h>
#include <string>

namespace TaxiGame
{

class Environment : public virtual GenericSingleton<Environment>
{
private:
	unsigned m_screenWidth;
	unsigned m_screenHeight;
	std::string m_iosVersion;
	std::string m_basePath;
	
public:
	Environment();
	
	void SetBasePath(const std::string &basePath);
	void SetScreenSize(unsigned width, unsigned height);
	void SetIOSVersion(const std::string &version);
	
	unsigned GetScreenWidth() const;
	unsigned GetScreenHeight() const;
	std::string GetIOSVersion() const;
	std::string GetBasePath() const;
};

#endif

}
