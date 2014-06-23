#include "GarageScreen.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include <Graphics/SpriteBatch.h>
#include "Control.h"
#include "GameController.h"
#include "Environment.h"
#include <Audio/SoundManager.h>

#include "Gui/StatusBar.h"

GarageScreen::GarageScreen(GameController *gameController) :
	m_gameController(gameController),
	m_carDealerButton(NULL),
	m_carPartsButton(NULL),
	m_carPaintButton(NULL)
{
}

GarageScreen::~GarageScreen(void)
{
}

bool GarageScreen::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	m_garageView = Inflater::Inflate(basePath + "data/gui/GaragePanel.xml");
	assert(m_garageView != NULL);

	StatusBar* statusBar = new StatusBar();
	m_garageView->AddChild(statusBar);

	m_carDealerButton = dynamic_cast<Control*>(m_garageView->FindChild("car_dealer"));
	assert(m_carDealerButton != NULL);

	m_carPartsButton = dynamic_cast<Control*>(m_garageView->FindChild("car_parts"));
	assert(m_carPartsButton != NULL);

	m_carPaintButton = dynamic_cast<Control*>(m_garageView->FindChild("car_paint"));
	assert(m_carPaintButton != NULL);

	ObsCast(IControlEventsObserver, m_carDealerButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_carPartsButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_carPaintButton)->AddObserver(this);

	return true;
}

bool GarageScreen::ReleaseResources()
{
	if (m_garageView != NULL)
		delete m_garageView;

	return true;
}

void GarageScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_garageView->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void GarageScreen::Update(float time, float seconds)
{
	m_garageView->Update(time, seconds);
}

void GarageScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_garageView->HandlePress(pointId, point);
}

void GarageScreen::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_garageView->HandleRelease(pointId, point);
}

void GarageScreen::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_garageView->HandleMove(pointId, point);
}

void GarageScreen::Enter()
{
}

void GarageScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_carDealerButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowCarDealerScreen();
	}
	else if (control == m_carPartsButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowCarPartsScreen();
	}
}
