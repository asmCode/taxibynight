#include "Inflater.h"
#include "Control.h"
#include "Label.h"
#include "AnimButton.h"
#include "InterfaceProvider.h"
#include "SpritesMap.h"
#include "Environment.h"
#include <Graphics/FontRenderer.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <stddef.h>
#include <assert.h>

Control* Inflater::Inflate(const std::string &xml)
{
	XMLNode *rootNode = XMLLoader::LoadFromFile(xml);
	if (rootNode == NULL)
		return NULL;

	Control *control = LoadNode(rootNode);

	return control;
}

Control* Inflater::LoadNode(XMLNode *node)
{
	std::string type = node->GetName();
	std::string name;
	if (node->HasAttrib("name"))
		name = node->GetAttribAsString("name");

	Control *control = NULL;

	if (type == "Panel")
		control = LoadPanelControl(node, name);
	else if (type == "Image")
		control = LoadImageControl(node, name);
	else if (type == "AnimButton")
		control = LoadAnimButtonControl(node, name);
	else if (type == "Label")
		control = LoadLabelControl(node, name);

	if (control == NULL)
		return NULL;

	LoadLayout(node, control);

	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		Control *childControl = LoadNode(node->GetChild(i));
		//assert(childControl != NULL);
		if (childControl == NULL)
			continue;

		control->AddChild(childControl);
	}

	return control;
}

void Inflater::LoadLayout(XMLNode *node, Control *control)
{
	uint32_t left = 0;
	uint32_t top = 0;
	uint32_t width = 0;
	uint32_t height = 0;
	bool fill = false;
	std::string align = "";

	if (node->HasAttrib("left"))
		left = node->GetAttribAsUInt32("left");
	if (node->HasAttrib("top"))
		top = node->GetAttribAsUInt32("top");
	if (node->HasAttrib("width"))
		width = node->GetAttribAsUInt32("width");
	if (node->HasAttrib("height"))
		height = node->GetAttribAsUInt32("height");
	if (node->HasAttrib("fill"))
		fill = node->GetAttribAsBool("fill");
	if (node->HasAttrib("align"))
		align = node->GetAttribAsString("align");

	control->SetBounds(left, top, width, height);
	control->SetFill(fill);
	control->SetAlign(align);
}

Control* Inflater::LoadImageControl(XMLNode *node, const std::string &name)
{
	std::string image;

	if (node->HasAttrib("image"))
		image = node->GetAttribAsString("image");

	TexPart *imageSprite = InterfaceProvider::GetSpritesMap()->GetTexPart(image);
	assert(imageSprite != NULL);

	return new Control(name, 0, 0, *imageSprite);
}

Control* Inflater::LoadLabelControl(XMLNode *node, const std::string &name)
{
	std::string text;
	float size = 1.0f;

	if (node->HasAttrib("text"))
		text = node->GetAttribAsString("text");
	if (node->HasAttrib("size"))
		size = node->GetAttribAsFloat("size");

	return new Label(name, text, InterfaceProvider::GetFontRenderer(), size, Color::White, 0, 0);
}

Control* Inflater::LoadPanelControl(XMLNode *node, const std::string &name)
{
	return new Control(name);
}

Control* Inflater::LoadAnimButtonControl(XMLNode *node, const std::string &name)
{
	std::string imageName;
	std::string imagePushedName;

	if (node->HasAttrib("image"))
		imageName = node->GetAttribAsString("image");
	if (node->HasAttrib("image_pushed"))
		imagePushedName = node->GetAttribAsString("image_pushed");

	TexPart *image = InterfaceProvider::GetSpritesMap()->GetTexPart(imageName);
	assert(image != NULL);

	TexPart *imagePushed = InterfaceProvider::GetSpritesMap()->GetTexPart(imagePushedName);
	assert(imagePushed != NULL);

	return new AnimButton(name, 0, 0, *image, *imagePushed);
}

