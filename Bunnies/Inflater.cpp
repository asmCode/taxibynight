#include "Inflater.h"
#include "Control.h"
#include "Label.h"
#include "AnimButton.h"
#include "Gui/GridPanel.h"
#include "InterfaceProvider.h"
#include "SpritesMap.h"
#include "Environment.h"
#include <Graphics/FontRenderer.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <stddef.h>
#include <assert.h>

float GetGuiScale()
{
	float screenHeight = (float)TaxiGame::Environment::GetInstance()->GetScreenHeight();

	if (screenHeight >= 720.0f)
		return 1.0f;
	else
		return screenHeight / 720.0f;
}

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
	else if (type == "Grid")
		control = LoadGridControl(node, name);
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
	float guiScale = GetGuiScale();

	if (node->HasAttrib("left"))
		control->SetX((int)((float)node->GetAttribAsUInt32("left") * guiScale));
	if (node->HasAttrib("top"))
		control->SetY((int)((float)node->GetAttribAsUInt32("top") * guiScale));
	if (node->HasAttrib("width"))
		control->SetWidth((int)((float)node->GetAttribAsUInt32("width") * guiScale));
	if (node->HasAttrib("height"))
		control->SetHeight((int)((float)node->GetAttribAsUInt32("height") * guiScale));
	if (node->HasAttrib("fill"))
		control->SetFill(node->GetAttribAsBool("fill"));
	if (node->HasAttrib("align"))
		control->SetAlign(node->GetAttribAsString("align"));
	if (node->HasAttrib("margin_left"))
		control->SetMarginLeft((int)((float)node->GetAttribAsInt32("margin_left") * guiScale));
	if (node->HasAttrib("margin_right"))
		control->SetMarginRight((int)((float)node->GetAttribAsInt32("margin_right") * guiScale));
	if (node->HasAttrib("margin_bottom"))
		control->SetMarginBottom((int)((float)node->GetAttribAsInt32("margin_bottom") * guiScale));
	if (node->HasAttrib("margin_top"))
		control->SetMarginTop((int)((float)node->GetAttribAsInt32("margin_top") * guiScale));
	if (node->HasAttrib("tmp_fill"))
		control->m_tmpFill = node->GetAttribAsString("tmp_fill");
}

Control* Inflater::LoadImageControl(XMLNode *node, const std::string &name)
{
	std::string image;
	float opacity = 1.0f;

	if (node->HasAttrib("image"))
		image = node->GetAttribAsString("image");
	if (node->HasAttrib("opacity"))
		opacity = node->GetAttribAsFloat("opacity");

	TexPart *imageSprite = InterfaceProvider::GetSpritesMap()->GetTexPart(image);
	assert(imageSprite != NULL);

	Control* control = new Control(name, 0, 0, *imageSprite);
	control->SetOpacity(opacity);

	return control;
}

Control* Inflater::LoadLabelControl(XMLNode *node, const std::string &name)
{
	float guiScale = GetGuiScale();

	std::string text;
	std::string font;
	Color color = Color::White;
	float size = 1.0f;

	if (node->HasAttrib("text"))
		text = node->GetAttribAsString("text");
	if (node->HasAttrib("font"))
		font = node->GetAttribAsString("font");
	if (node->HasAttrib("size"))
		size = node->GetAttribAsFloat("size");
	if (node->HasAttrib("color"))
	{
		std::string colorTxt = node->GetAttribAsString("color");
		int r, g, b;
		sscanf(colorTxt.c_str(), "%d;%d;%d", &r, &g, &b);
		color.R = (unsigned char)r;
		color.G = (unsigned char)g;
		color.B = (unsigned char)b;
	}

	return new Label(name, text, InterfaceProvider::GetFontRenderer(font), size * guiScale, color, 0, 0);
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

Control* Inflater::LoadGridControl(XMLNode *node, const std::string &name)
{
	return new GridPanel(name);
}

