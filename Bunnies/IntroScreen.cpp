#include "IntroScreen.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include <Graphics/SpriteBatch.h>
#include "Control.h"
#include "GameController.h"
#include "Environment.h"
#include <Audio/SoundManager.h>

IntroScreen::IntroScreen(GameController *gameController) :
	m_gameController(gameController),
	m_nextButton(NULL)
{
}

IntroScreen::~IntroScreen(void)
{
}

bool IntroScreen::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	m_introView = Inflater::Inflate(basePath + "data/gui/IntroPanel.xml");
	assert(m_introView != NULL);

	m_nextButton = dynamic_cast<Control*>(m_introView->FindChild("next"));
	assert(m_nextButton != NULL);

	ObsCast(IControlEventsObserver, m_nextButton)->AddObserver(this);

	return true;
}

bool IntroScreen::ReleaseResources()
{
	if (m_introView != NULL)
		delete m_introView;

	return true;
}

void IntroScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_introView->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void IntroScreen::Update(float time, float seconds)
{
	m_introView->Update(time, seconds);
}

void IntroScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_introView->HandlePress(pointId, point);
}

void IntroScreen::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_introView->HandleRelease(pointId, point);
}

void IntroScreen::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_introView->HandleMove(pointId, point);
}

void IntroScreen::Enter()
{
}

void IntroScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_nextButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowMainMenuScreen();
	}
}