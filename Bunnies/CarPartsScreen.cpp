#include "CarPartsScreen.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include "Car.h"
#include "Player.h"
#include "Control.h"
#include "GameController.h"
#include "Environment.h"
#include "Gui/ProgressControl.h"
#include "Gui/StatusBar.h"
#include <Audio/SoundManager.h>
#include <Graphics/SpriteBatch.h>

CarPartsScreen::CarPartsScreen(GameController *gameController) :
	m_gameController(gameController),
	m_speedProgress(NULL),
	m_accProgress(NULL),
	m_tiresProgress(NULL),
	m_statusBar(NULL)
{
}

CarPartsScreen::~CarPartsScreen(void)
{
}

bool CarPartsScreen::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	m_view = Inflater::Inflate(basePath + "data/gui/CarPartsPanel.xml");
	assert(m_view != NULL);

	m_speedProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("speed"));
	assert(m_speedProgress != NULL);

	m_accProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("acc"));
	assert(m_accProgress != NULL);

	m_tiresProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("tires"));
	assert(m_tiresProgress != NULL);

	m_statusBar = dynamic_cast<StatusBar*>(m_view->FindChild("status_bar"));
	assert(m_statusBar != NULL);

	/*

	ObsCast(IControlEventsObserver, m_car1Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car2Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car3Button)->AddObserver(this);

	*/

	RefreshView();

	return true;
}

bool CarPartsScreen::ReleaseResources()
{
	if (m_view != NULL)
		delete m_view;

	return true;
}

void CarPartsScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_view->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void CarPartsScreen::Update(float time, float seconds)
{
	m_view->Update(time, seconds);
}

void CarPartsScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_view->HandlePress(pointId, point);
}

void CarPartsScreen::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_view->HandleRelease(pointId, point);
}

void CarPartsScreen::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_view->HandleMove(pointId, point);
}

void CarPartsScreen::Enter()
{
}

void CarPartsScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	/*if (control == m_car1Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowMainMenuScreen();
	}*/
}

void CarPartsScreen::RefreshView()
{
	Car* car = Player::Instance->GetActiveCar();
	if (car == NULL)
		return;
	
	int totalSlots;
	int activeSlots;
	car->GetUpgradeSlots(UpgradeId::Speed, totalSlots, activeSlots);
	m_speedProgress->SetLimit(totalSlots);
	m_speedProgress->SetValue(activeSlots);

	car->GetUpgradeSlots(UpgradeId::Acc, totalSlots, activeSlots);
	m_accProgress->SetLimit(totalSlots);
	m_accProgress->SetValue(activeSlots);

	car->GetUpgradeSlots(UpgradeId::Tires, totalSlots, activeSlots);
	m_tiresProgress->SetLimit(totalSlots);
	m_tiresProgress->SetValue(activeSlots);
}
