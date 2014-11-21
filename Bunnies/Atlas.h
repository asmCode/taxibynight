#pragma once

#include <map>
#include <string>

class TexPart;
class Content;

class Atlas
{
public:
	Atlas();
	~Atlas();

	// path with "/", without filename
	bool LoadFromFile(const std::string &path, const std::string& atlasName, Content *content);
	TexPart* GetTexPart(const std::string &name);

private:
	std::map<std::string, TexPart*> m_sprites;
};
