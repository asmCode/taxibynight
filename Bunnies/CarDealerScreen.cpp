#include "CarDealerScreen.h"
#include "Inflater.h"
#include "Car.h"
#include "Player.h"
#include "InterfaceProvider.h"
#include "Control.h"
#include "Label.h"
#include "Gui/ProgressControl.h"
#include "GameController.h"
#include "Environment.h"
#include "GlobalSettings/GlobalSettings.h"
#include <Graphics/SpriteBatch.h>
#include <Utils/StringUtils.h>
#include <Audio/SoundManager.h>

CarDealerScreen::CarDealerScreen(GameController *gameController) :
	m_gameController(gameController),
	m_backButton(NULL),
	m_car1Button(NULL),
	m_car2Button(NULL),
	m_car3Button(NULL),
	m_buyPanel(NULL),
	m_activatePanel(NULL),
	m_alreadyHavePanel(NULL),
	m_buySoftButton(NULL),
	m_buyHardButton(NULL),
	m_activateButton(NULL),
	m_softPriceLabel(NULL),
	m_hardPriceLabel(NULL),
	m_carNameLabel(NULL),
	m_speedProgress(NULL),
	m_accProgress(NULL),
	m_tiresProgress(NULL),
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

	m_backButton = dynamic_cast<Control*>(m_view->FindChild("back_btn"));
	assert(m_backButton != NULL);

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

	m_softPriceLabel = dynamic_cast<Label*>(m_view->FindChild("soft_price"));
	assert(m_softPriceLabel != NULL);
	m_hardPriceLabel = dynamic_cast<Label*>(m_view->FindChild("hard_price"));
	assert(m_hardPriceLabel != NULL);
	m_carNameLabel = dynamic_cast<Label*>(m_view->FindChild("car_name"));
	assert(m_carNameLabel != NULL);

	m_speedProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("speed"));
	assert(m_speedProgress != NULL);
	m_accProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("acc"));
	assert(m_accProgress != NULL);
	m_tiresProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("tires"));
	assert(m_tiresProgress != NULL);

	ObsCast(IControlEventsObserver, m_backButton)->AddObserver(this);
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
			// not enouch soft money - message
			assert("not enouch soft money - message" && false);
		}

		Player::Instance->SetSoftMoney(Player::Instance->GetSoftMoney() - carData.SoftPrice);
	}
	else
	{
		assert(carData.HardPrice > 0);

		if (Player::Instance->GetHardMoney() < carData.HardPrice)
		{
			// not enouch hard money - message
			assert("not enouch hard money - message" && false);
		}

		Player::Instance->SetHardMoney(Player::Instance->GetHardMoney() - carData.HardPrice);
	}

	Player::Instance->AddCar(carId);

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

void CarDealerScreen::RefreshCarStatistics()
{
	if (Player::Instance->HasCar(m_selectedCarId))
	{
		Car* car = Player::Instance->GetCar(m_selectedCarId);
		assert(car != NULL);

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
	else
	{
		CarData carData = GlobalSettings::GetCarById(m_selectedCarId);

		m_speedProgress->SetLimit(carData.SpeedSlots);
		m_speedProgress->SetValue(carData.SpeedSlots - carData.GetUpgradeSlotsCount(UpgradeId::Speed));
		m_accProgress->SetLimit(carData.AccSlots);
		m_accProgress->SetValue(carData.AccSlots - carData.GetUpgradeSlotsCount(UpgradeId::Acc));
		m_tiresProgress->SetLimit(carData.TiresSlots);
		m_tiresProgress->SetValue(carData.TiresSlots - carData.GetUpgradeSlotsCount(UpgradeId::Tires));
	}
}

void CarDealerScreen::RefreshView()
{
	CarData carData = GlobalSettings::GetCarById(m_selectedCarId);

	m_carNameLabel->SetText(carData.Name);

	HideAllActionPanels();

	if (m_activeCar == NULL || !Player::Instance->HasCar(m_selectedCarId))
	{
		m_buyPanel->SetVisible(true);

		m_softPriceLabel->SetText(StringUtils::ToString(carData.SoftPrice));
		m_hardPriceLabel->SetText(StringUtils::ToString(carData.HardPrice));

		if (carData.SoftPrice > 0 && carData.HardPrice > 0)
		{
			m_buySoftButton->SetAlign("bottom-left");
			m_buySoftButton->SetVisible(true);
			m_buyHardButton->SetAlign("bottom-right");
			m_buyHardButton->SetVisible(true);
		}
		else if (carData.SoftPrice > 0)
		{
			m_buySoftButton->SetAlign("bottom");
			m_buySoftButton->SetVisible(true);
			m_buyHardButton->SetVisible(false);
		}
		else if (carData.HardPrice > 0)
		{
			m_buyHardButton->SetAlign("bottom");
			m_buyHardButton->SetVisible(true);
			m_buySoftButton->SetVisible(false);
		}
	}
	else if (m_activeCar->GetId() == m_selectedCarId)
		m_alreadyHavePanel->SetVisible(true);
	else if (Player::Instance->HasCar(m_selectedCarId))
		m_activatePanel->SetVisible(true);

	RefreshCarStatistics();
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
	
	SelectCar(CarId::Car1);
	RefreshView();
}

void CarDealerScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_backButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowGarageScreen();
	}
	else if (control == m_car1Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car1);
		RefreshView();
	}
	else if (control == m_car2Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car2);
		RefreshView();
	}
	else if (control == m_car3Button)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		SelectCar(CarId::Car3);
		RefreshView();
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
