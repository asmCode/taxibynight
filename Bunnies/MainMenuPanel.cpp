#include "MainMenuPanel.h"
#include "Environment.h"
#include "InterfaceProvider.h"
#include "AnimButton.h"
#include "SpritesMap.h"
#include "GameController.h"
#include <Graphics/TexPart.h>
#include <Graphics/Content/Content.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
//#include "MessageBox.h"
//#include "SoundManager.h"

MainMenuPanel::MainMenuPanel(GameController *gameController) :
	Control("MainMenuPanel"),
	m_gameController(gameController)
{
}

MainMenuPanel *MainMenuPanel::Create(GameController *gameController)
{	
	MainMenuPanel *ret = new MainMenuPanel(gameController);
	if (ret != NULL)
	{		
		ret ->x = 0;
		ret ->y = 0;
		ret ->width = Environment::GetInstance()->GetScreenWidth();
		ret ->height = Environment::GetInstance()->GetScreenHeight();

		std::string basePath = Environment::GetInstance()->GetBasePath();
		XMLNode *root = XMLLoader::LoadFromFile(basePath + "/data/gui/MainMenuPanel.xml");
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
		}
	}
	
	return ret;
}

void MainMenuPanel::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control->GetName() == "start_game_btn")
		m_gameController->ShowGameScreen();
}

void MainMenuPanel::OnDraw(float time, float seconds)
{
	this->Control::OnDraw(time, seconds);
}

