#include "GarageScreen.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include "Control.h"
#include "GameController.h"
#include "CarDealerPanelController.h"
#include "CarPartsPanelController.h"
#include "Environment.h"
#include "Gui/StatusBar.h"
#include "ControlAnimation.h"
#include <Graphics/SpriteBatch.h>
#include <Audio/SoundManager.h>


GarageScreen::GarageScreen(GameController *gameController) :
	m_gameController(gameController),
	m_carDealerButton(NULL),
	m_carPartsButton(NULL),
	m_carPaintButton(NULL),
	m_carDealerPanelController(NULL),
	m_viewAnim(NULL),
	m_statusBar(NULL)
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

	Control* carDealerPanel = m_garageView->FindChild("car_dealer_panel");
	assert(carDealerPanel != NULL);
	m_carDealerPanelController = new CarDealerPanelController(m_gameController, carDealerPanel);
	m_carDealerPanelController->InitResources();

	Control* carPartsPanel = m_garageView->FindChild("car_parts_panel");
	assert(carPartsPanel != NULL);
	m_carPartsPanelController = new CarPartsPanelController(m_gameController, carPartsPanel);
	m_carPartsPanelController->InitResources();

	m_carDealerButton = dynamic_cast<Control*>(m_garageView->FindChild("car_dealer"));
	assert(m_carDealerButton != NULL);

	m_carPartsButton = dynamic_cast<Control*>(m_garageView->FindChild("car_parts"));
	assert(m_carPartsButton != NULL);

	m_carPaintButton = dynamic_cast<Control*>(m_garageView->FindChild("car_paint"));
	assert(m_carPaintButton != NULL);

	m_statusBar = dynamic_cast<StatusBar*>(m_garageView->FindChild("status_bar"));
	assert(m_statusBar != NULL);

	m_viewAnim = ControlAnimation::LoadFromFile("data/gui/GaragePanelIntroAnimation.xml");
	assert(m_viewAnim != NULL);

	m_viewAnim->SetTarget(m_garageView);

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
	static float f = 0.0f;
	f += seconds;
	if (f > 2)
		m_viewAnim->Update(seconds);
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
	m_carDealerPanelController->SetActive(false);
	m_carPartsPanelController->SetActive(false);
}

void GarageScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_carDealerButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		ShowCarDealerPanel();
	}
	else if (control == m_carPartsButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		ShowCarPartsPanel();
	}
}

void GarageScreen::ShowCarDealerPanel()
{
	m_carPartsPanelController->SetActive(false);

	m_carDealerPanelController->SetActive(true);
	m_carDealerPanelController->Enter();
}

void GarageScreen::ShowCarPartsPanel()
{
	m_carDealerPanelController->SetActive(false);

	m_carPartsPanelController->SetActive(true);
	m_carPartsPanelController->Enter();
}
