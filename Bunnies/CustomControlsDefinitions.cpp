#include "CustomControlsDefinitions.h"
#include <IO/Path.h>
#include <vector>

void CustomControlsDefinitions::LoadControlsFromPath(const std::string& path)
{
	std::vector<std::string> filenames;
	Path::GetAllFiles(filenames, path, "*.xml");

	for (uint32_t i = 0; i < filenames.size(); i++)
	{
		std::string code = Path::GetFileContentAsText((path + filenames[i]).c_str());
		Path filenameOnly(filenames[i]);

		m_controlsDefinitions[filenameOnly.GetFilename()] = code;
	}
}

std::string CustomControlsDefinitions::GetControlDefinition(const std::string& name)
{
	ControlsDefinitionsMap::iterator it = m_controlsDefinitions.find(name);
	if (it == m_controlsDefinitions.end())
		return "";

	return it->second;
}
