#pragma once

#include <string>
#include <map>

class CustomControlsDefinitions
{
public:
	void LoadControlsFromPath(const std::string& path);

	std::string GetControlDefinition(const std::string& name);

private:
	typedef std::map<std::string, std::string> ControlsDefinitionsMap;

	ControlsDefinitionsMap m_controlsDefinitions;
};
