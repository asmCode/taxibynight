#include "CarDealerScreen.h"
#include "Inflater.h"
#include "Car.h"
#include "Player.h"
#include "GlobalSettings/GlobalSettings.h"
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
	m_buySoftButton(NULL),
	m_buyHardButton(NULL),
	m_activateButton(NULL),
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

	m_buySoftButton = m_view->FindChild("buy_soft_btn");
	assert(m_buySoftButton != NULL);
	m_buyHardButton = m_view->FindChild("buy_hard_btn");
	assert(m_buyHardButton != NULL);
	m_activateButton = m_view->FindChild("activate_btn");
	assert(m_activateButton != NULL);

	ObsCast(IControlEventsObserver, m_car1Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car2Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_car3Button)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buySoftButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyHardButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_activateButton)->AddObserver(this);

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

void CarDealerScreen::BuyCar(const std::string& carId, bool buyForHard)
{
	assert(Player::Instance->HasCar(carId) == false);
	if (Player::Instance->HasCar(carId))
		return;

	CarData carData = GlobalSettings::GetCarById(carId);

	if (!buyForHard)
	{
		assert(carData.SoftPrice > 0);

		if (Player::Instance->GetSoftMoney() < carData.SoftPrice)
		{
			// not enouch money - message
			assert("not enouch money - message" && false);
		}

		Player::Instance->SetSoftMoney(Player::Instance->GetSoftMoney() - carData.SoftPrice);
		Player::Instance->AddCar(carId);
	}

	ActivateCar(carId);
}

void CarDealerScreen::ActivateCar(const std::string& carId)
{
	assert(Player::Instance->HasCar(carId));
	if (!Player::Instance->HasCar(carId))
		return;

	Player::Instance->ActicateCar(carId);

	m_activeCar = Player::Instance->GetActiveCar();

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
	else if (control == m_buySoftButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		BuyCar(m_selectedCarId, false);
	}
	else if (control == m_buyHardButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		BuyCar(m_selectedCarId, true);
	}
	else if (control == m_activateButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		ActivateCar(m_selectedCarId);
	}
}
