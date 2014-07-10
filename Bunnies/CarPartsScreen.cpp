#include "CarPartsScreen.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include "Car.h"
#include "Player.h"
#include "Control.h"
#include "Label.h"
#include "GameController.h"
#include "Environment.h"
#include "Gui/ProgressControl.h"
#include "Gui/StatusBar.h"
#include <Audio/SoundManager.h>
#include <Graphics/SpriteBatch.h>
#include <Utils/Log.h>
#include <Utils/StringUtils.h>

CarPartsScreen::CarPartsScreen(GameController *gameController) :
	m_gameController(gameController),
	m_backButton(NULL),
	m_speedProgress(NULL),
	m_accProgress(NULL),
	m_tiresProgress(NULL),
	m_statusBar(NULL),
	m_buySpeedButton(NULL),
	m_buyAccButton(NULL),
	m_buyTiresButton(NULL),
	m_speedPrice(NULL),
	m_accPrice(NULL),
	m_tiresPrice(NULL)
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

	m_backButton = dynamic_cast<Control*>(m_view->FindChild("back_btn"));
	assert(m_backButton != NULL);

	m_speedProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("speed"));
	assert(m_speedProgress != NULL);
	m_accProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("acc"));
	assert(m_accProgress != NULL);
	m_tiresProgress = dynamic_cast<ProgressControl*>(m_view->FindChild("tires"));
	assert(m_tiresProgress != NULL);

	m_buySpeedButton = dynamic_cast<Control*>(m_view->FindChild("buy_speed_btn"));
	assert(m_buySpeedButton != NULL);
	m_buyAccButton = dynamic_cast<Control*>(m_view->FindChild("buy_acc_btn"));
	assert(m_buyAccButton != NULL);
	m_buyTiresButton = dynamic_cast<Control*>(m_view->FindChild("buy_tires_btn"));
	assert(m_buyTiresButton != NULL);

	m_speedPrice = dynamic_cast<Label*>(m_view->FindChild("speed_price"));
	assert(m_speedPrice != NULL);
	m_accPrice = dynamic_cast<Label*>(m_view->FindChild("acc_price"));
	assert(m_accPrice != NULL);
	m_tiresPrice = dynamic_cast<Label*>(m_view->FindChild("tires_price"));
	assert(m_tiresPrice != NULL);

	m_statusBar = dynamic_cast<StatusBar*>(m_view->FindChild("status_bar"));
	assert(m_statusBar != NULL);

	ObsCast(IControlEventsObserver, m_backButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buySpeedButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyAccButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyTiresButton)->AddObserver(this);

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
	m_activeCar = Player::Instance->GetActiveCar();
	if (m_activeCar == NULL)
		return;

	m_activeCar->AddObserver(this);

	RefreshView();
}

void CarPartsScreen::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_backButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		m_gameController->ShowGarageScreen();
	}
	else if (control == m_buySpeedButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		Upgrade(UpgradeId::Speed);
	}
	else if (control == m_buyAccButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		Upgrade(UpgradeId::Acc);
	}
	else if (control == m_buyTiresButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		Upgrade(UpgradeId::Tires);
	}
}

void CarPartsScreen::RefreshView()
{
	RefreshUpgradeProgress(UpgradeId::Speed, m_speedProgress, m_speedPrice);
	RefreshUpgradeProgress(UpgradeId::Acc, m_accProgress, m_accPrice);
	RefreshUpgradeProgress(UpgradeId::Tires, m_tiresProgress, m_tiresPrice);
}

void CarPartsScreen::RefreshUpgradeProgress(
	const std::string& upgradeId,
	ProgressControl* progressControl,
	Label* upgradePrice)
{
	if (m_activeCar == NULL)
	{
		assert(false);
		return;
	}

	int totalSlots;
	int activeSlots;
	m_activeCar->GetUpgradeSlots(upgradeId, totalSlots, activeSlots);
	progressControl->SetLimit(totalSlots);
	progressControl->SetValue(activeSlots);

	if (m_activeCar->IsFullyUpgraded(upgradeId))
	{
		//upgradePrice->SetVisible(false);
	}
	else
	{
		//upgradePrice->SetVisible(true);

		float softPrice;
		float hardPrice;
		m_activeCar->GetNextUpgradePrice(upgradeId, softPrice, hardPrice);
		upgradePrice->SetText(StringUtils::ToString(softPrice));
	}
}

void CarPartsScreen::Upgrade(const std::string& upgradeId)
{
	if (m_activeCar == NULL)
	{
		assert(false);
		return;
	}

	if (m_activeCar->IsFullyUpgraded(upgradeId))
		return;

	float softPrice;
	float hardPrice;
	m_activeCar->GetNextUpgradePrice(upgradeId, softPrice, hardPrice);

	m_activeCar->Upgrade(upgradeId);

	Player::Instance->SetSoftMoney(Player::Instance->GetSoftMoney() - softPrice);
}

void CarPartsScreen::Upgraded(Car* car, const std::string& upgradeId)
{
	RefreshView();
}
