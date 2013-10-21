#include "HUD.h"
#include "Environment.h"
#include "InterfaceProvider.h"
#include "AnimButton.h"
#include "Label.h"
#include "SpritesMap.h"
#include "GameScreen.h"
#include "GameController.h"
#include <Graphics/TexPart.h>
#include <Graphics/Content/Content.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
//#include "MessageBox.h"
//#include "SoundManager.h"

HUD::HUD() :
	Control("HUD")
{
}

HUD *HUD::Create(GameScreen *gameScreen)
{	
	HUD *ret = new HUD();
	if (ret != NULL)
	{		
		ret->m_gameScreen = gameScreen;

		ret ->x = 0;
		ret ->y = 0;
		ret ->width = TaxiGame::Environment::GetInstance()->GetScreenWidth();
		ret ->height = TaxiGame::Environment::GetInstance()->GetScreenHeight();

		std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();
		XMLNode *root = XMLLoader::LoadFromFile(basePath + "data/gui/HUD.xml");
		if (root == NULL)
			return NULL;

		for (uint32_t i = 0; i < root->GetChildrenCount(); i++)
		{
			XMLNode &childDesc = (*root)[i];

			std::string type = childDesc.GetName();
			std::string name = childDesc.GetAttribAsString("name");
			uint32_t left = childDesc.GetAttribAsUInt32("left");
			uint32_t top = childDesc.GetAttribAsUInt32("top");

			if (type == "AnimButton")
			{
				std::string imageName = childDesc.GetAttribAsString("image");
				std::string imagePushedName = childDesc.GetAttribAsString("image_pushed");

				TexPart *image = InterfaceProvider::GetSpritesMap()->GetTexPart(imageName);
				assert(image != NULL);

				TexPart *imagePushed = InterfaceProvider::GetSpritesMap()->GetTexPart(imagePushedName);
				assert(imagePushed != NULL);

				AnimButton *ctrl = new AnimButton(name, left, top, *image, *imagePushed);

				ret->AddChild(ctrl);

				ObsCast(IControlEventsObserver, ctrl)->AddObserver(ret);
			}
			else if (type == "Image")
			{
				std::string imageName = childDesc.GetAttribAsString("image");

				TexPart *image = InterfaceProvider::GetSpritesMap()->GetTexPart(imageName);
				assert(image != NULL);

				Control *ctrl = new Control(name, left, top, *image);

				ret->AddChild(ctrl);
			}
			else if (type == "Label")
			{
				std::string text = childDesc.GetAttribAsString("text");
				float size = childDesc.GetAttribAsFloat("size");

				Label *ctrl = new Label("current_money", text, InterfaceProvider::GetFontRenderer(), size, Color::White, left, top);
				ret->AddChild(ctrl);
			}
		}
	}
	
	return ret;
}

void HUD::Clicked(Control *control, uint32_t x, uint32_t y)
{
}

void HUD::Pressed(Control *control, uint32_t x, uint32_t y)
{
	if (control->GetName() == "turn_left")
		m_gameScreen->TurnLeftButtonPressed(true);
	else if (control->GetName() == "turn_right")
		m_gameScreen->TurnRightButtonPressed(true);
	if (control->GetName() == "acc_pedal")
		m_gameScreen->AccelerationButtonPressed(true);
}

void HUD::Released(Control *control, uint32_t x, uint32_t y)
{
	if (control->GetName() == "turn_left")
		m_gameScreen->TurnLeftButtonPressed(false);
	else if (control->GetName() == "turn_right")
		m_gameScreen->TurnRightButtonPressed(false);
	if (control->GetName() == "acc_pedal")
		m_gameScreen->AccelerationButtonPressed(false);
}

void HUD::OnDraw(float time, float seconds)
{
	this->Control::OnDraw(time, seconds);
}

