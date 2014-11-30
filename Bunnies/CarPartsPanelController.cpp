#include "CarPartsPanelController.h"
#include "Inflater.h"
#include "InterfaceProvider.h"
#include "Car.h"
#include "Player.h"
#include "Control.h"
#include "Label.h"
#include "GameController.h"
#include "Environment.h"
#include "Gui/ProgressControl.h"
#include <Audio/SoundManager.h>
#include <Graphics/SpriteBatch.h>
#include <Utils/Log.h>
#include <Utils/StringUtils.h>

CarPartsPanelController::CarPartsPanelController(GameController *gameController, Control* view) :
	m_gameController(gameController),
	m_view(view),
	m_speedProgress(NULL),
	m_accProgress(NULL),
	m_tiresProgress(NULL),
	m_buySpeedButton(NULL),
	m_buyAccButton(NULL),
	m_buyTiresButton(NULL),
	m_speedPrice(NULL),
	m_accPrice(NULL),
	m_tiresPrice(NULL)
{
}

CarPartsPanelController::~CarPartsPanelController(void)
{
}

bool CarPartsPanelController::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

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

	ObsCast(IControlEventsObserver, m_buySpeedButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyAccButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyTiresButton)->AddObserver(this);

	return true;
}

bool CarPartsPanelController::ReleaseResources()
{
	if (m_view != NULL)
		delete m_view;

	return true;
}

void CarPartsPanelController::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_view->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void CarPartsPanelController::Update(float time, float seconds)
{
	m_view->Update(time, seconds);
}

void CarPartsPanelController::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_view->HandlePress(pointId, point);
}

void CarPartsPanelController::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_view->HandleRelease(pointId, point);
}

void CarPartsPanelController::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_view->HandleMove(pointId, point);
}

void CarPartsPanelController::Enter()
{
	m_activeCar = Player::Instance->GetActiveCar();
	if (m_activeCar == NULL)
		return;

	m_activeCar->AddObserver(this);

	RefreshView();
}

void CarPartsPanelController::SetActive(bool active)
{
	m_view->SetVisible(active);
}

void CarPartsPanelController::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_buySpeedButton)
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

void CarPartsPanelController::RefreshView()
{
	RefreshUpgradeProgress(UpgradeId::Speed, m_speedProgress, m_speedPrice);
	RefreshUpgradeProgress(UpgradeId::Acc, m_accProgress, m_accPrice);
	RefreshUpgradeProgress(UpgradeId::Tires, m_tiresProgress, m_tiresPrice);
}

void CarPartsPanelController::RefreshUpgradeProgress(
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

void CarPartsPanelController::Upgrade(const std::string& upgradeId)
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

void CarPartsPanelController::Upgraded(Car* car, const std::string& upgradeId)
{
	RefreshView();
}
