#pragma once

#include <string>

class XMLNode;

class ICustomControl
{
public:
	virtual void InitializeCustomControl(const std::string& name, XMLNode* node) = 0;
};
