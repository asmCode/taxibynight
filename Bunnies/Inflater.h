#pragma once

#include <string>

class Control;
class XMLNode;

class Inflater
{	
public:
	static Control* Inflate(const std::string &xml, bool fromCode = false);

private:
	static Control* LoadImageControl(XMLNode *node, const std::string &name);
	static Control* LoadSpriteControl(XMLNode *node, const std::string &name);
	static Control* LoadAnimButtonControl(XMLNode *node, const std::string &name);
	static Control* LoadGridControl(XMLNode *node, const std::string &name);
	static Control* LoadProgressControl(XMLNode *node, const std::string &name);
	static Control* LoadLabelControl(XMLNode *node, const std::string &name);
	static Control* LoadPanelControl(XMLNode *node, const std::string &name);
	static Control* LoadStatusBar(XMLNode *node, const std::string &name);
	static Control* LoadProgressBar(XMLNode *node, const std::string &name);
	static Control* LoadCustomControl(XMLNode *node, const std::string &type, const std::string &name);
	static Control* LoadNode(XMLNode *node);
	static void LoadLayout(XMLNode *node, Control *control);
};

