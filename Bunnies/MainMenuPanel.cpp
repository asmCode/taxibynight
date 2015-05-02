#include "MainMenuPanel.h"
#include "Control.h"
#include "Environment.h"
#include "InterfaceProvider.h"
#include "GameController.h"
#include "Inflater.h"
#include "Audio/SoundManager.h"
//#include "MessageBox.h"
//#include "SoundManager.h"

MainMenuPanel::MainMenuPanel(GameController *gameController) :
	Control("MainMenuPanel"),
	m_gameController(gameController)
{
	SetFill(true);
}

MainMenuPanel *MainMenuPanel::Create(GameController *gameController)
{	
	MainMenuPanel *ret = new MainMenuPanel(gameController);

	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	Control *content = Inflater::Inflate(basePath + "gui/MainMenuPanel.xml");
	if (content == NULL)
		return NULL;

	Control *startButton = content->FindChild("start_game_btn");
	if (startButton != NULL)
		ObsCast(IControlEventsObserver, startButton)->AddObserver(ret);

	Control *leaderButton = content->FindChild("leaderboard_button");
	if (leaderButton != NULL)
		ObsCast(IControlEventsObserver, leaderButton)->AddObserver(ret);
	

	ret->AddChild(content);

	return ret;
}

void MainMenuPanel::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control->GetName() == "start_game_btn")
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowGameScreen();
	}
	else if (control->GetName() == "leaderboard_button")
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowLeaderboard();
	}
}

void MainMenuPanel::OnDraw(float time, float seconds)
{
	this->Control::OnDraw(time, seconds);
}

