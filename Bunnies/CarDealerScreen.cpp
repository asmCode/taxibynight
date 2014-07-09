#include "CarDealerScreen.h"
#include "Inflater.h"
#include "Car.h"
#include "Player.h"
#include "InterfaceProvider.h"
#include <Graphics/SpriteBatch.h>
#include "Control.h"
#include "GameController.h"
#include "Environment.h"
#include <Audio/SoundManager.h>

CarDealerScreen::CarDealerScreen(GameController *gameController) :
	m_gameController(gameController),
	m_car1Button(NULL),
	m_car2Button(NULL),
	m_car3Button(NULL),
	m_buyPanel(NULL),
	m_activatePanel(NULL),
	m_alreadyHavePanel(NULL),
	m_activeCar(NULL)
{
}

CarDealerScreen::~CarDealerScreen(void)
{
}

bool CarDealerScreen::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	m_view = Inflater::Inflate(basePath + "data/gui/CarDealerPanel.xml");
	assert(m_view != NULL);

	m_car1Button = dynamic_cast<Control*>(m_view->FindChild("car_1_button"));
	assert(m_car1Button != NULL);

	m_car2Button = dynamic_cast<Control*>(m_view->FindChild("car_2_button"));
	assert(m_car2Button != NULL);

	m_car3Button = dynamic_cast<Control*>(m_view->FindChild("car_3_button"));
	assert(m_car3Button != NULL);

	m_buyPanel = m_view->FindChild("buy_panel");
	assert(m_buyPanel != NULL);
	m_activatePanel = m_view->FindChild("activate_panel");
	assert(m_activatePanel != NULL);
	m_alreadyHavePanel = m_view->FindChild("already_have_panel");
	assert(m_alreadyHavePanel != NULL);

	ObsCast(IControlEventsObserver, m_car1Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car2Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car3Button)->AddObserver(this);

	return true;
}

bool CarDealerScreen::ReleaseResources()
{
	if (m_view != NULL)
		delete m_view;

	return true;
}

void CarDealerScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_view->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void CarDealerScreen::Update(float time, float seconds)
{
	m_view->Update(time, seconds);
}

void CarDealerScreen::SelectCar(const std::string& carId)
{
	if (carId == m_selectedCarId)
		return;

	m_selectedCarId = carId;

	RefreshView();
}

void CarDealerScreen::HideAllActionPanels()
{
	m_buyPanel->SetVisible(false);
	m_activatePanel->SetVisible(false);
	m_alreadyHavePanel->SetVisible(false);
}

void CarDealerScreen::RefreshView()
{
	HideAllActionPanels();

	if (m_activeCar->GetId() == m_selectedCarId)
		m_alreadyHavePanel->SetVisible(true);
	else if (Player::Instance->HasCar(m_selectedCarId))
		m_activatePanel->SetVisible(true);
	else
		m_buyPanel->SetVisible(true);
}

void CarDealerScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_view->HandlePress(pointId, point);
}

void CarDealerScreen::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_view->HandleRelease(pointId, point);
}

void CarDealerScreen::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_view->HandleMove(pointId, point);
}

void CarDealerScreen::Enter()
{
	m_activeCar = Player::Instance->GetActiveCar();
	if (m_activeCar == NULL)
		return;

	SelectCar(CarId::Car1);
}

void CarDealerScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_car1Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car1);
	}
	else if (control == m_car2Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car2);
	}
	else if (control == m_car3Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car3);
	}
}
