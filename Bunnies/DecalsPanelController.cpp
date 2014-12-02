#include "DecalsPanelController.h"
#include "Inflater.h"
#include "Car.h"
#include "Player.h"
#include "Atlas.h"
#include "InterfaceProvider.h"
#include "Control.h"
#include "GuiCar.h"
#include "GuiCarUtils.h"
#include "AnimButton.h"
#include "Label.h"
#include "Gui/ProgressControl.h"
#include "Gui/GridPanel.h"
#include "AnimButton.h"
#include "GameController.h"
#include "Environment.h"
#include "GlobalSettings/GlobalSettings.h"
#include <Graphics/SpriteBatch.h>
#include <Utils/StringUtils.h>
#include <Audio/SoundManager.h>

DecalsPanelController::DecalsPanelController(GameController *gameController, Control* view, GuiCar* guiCar) :
	m_gameController(gameController),
	m_guiCar(guiCar),
	m_view(view),
	m_buyPanel(NULL),
	m_activatePanel(NULL),
	m_buySoftButton(NULL),
	m_buyHardButton(NULL),
	m_activateButton(NULL),
	m_softPriceLabel(NULL),
	m_hardPriceLabel(NULL),
	m_decalButtonsGrid(NULL),
	m_activeCar(NULL)
{
}

DecalsPanelController::~DecalsPanelController(void)
{
}

bool DecalsPanelController::InitResources()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	m_buyPanel = m_view->FindChild("buy_panel");
	assert(m_buyPanel != NULL);
	m_activatePanel = m_view->FindChild("activate_panel");
	assert(m_activatePanel != NULL);

	m_buySoftButton = m_view->FindChild("buy_soft_btn");
	assert(m_buySoftButton != NULL);
	m_buyHardButton = m_view->FindChild("buy_hard_btn");
	assert(m_buyHardButton != NULL);
	m_activateButton = m_view->FindChild("activate_btn");
	assert(m_activateButton != NULL);

	m_decalButtonsGrid = dynamic_cast<GridPanel*>(m_view->FindChild("decals_grid"));
	assert(m_decalButtonsGrid != NULL);

	m_softPriceLabel = dynamic_cast<Label*>(m_view->FindChild("soft_price"));
	assert(m_softPriceLabel != NULL);
	m_hardPriceLabel = dynamic_cast<Label*>(m_view->FindChild("hard_price"));
	assert(m_hardPriceLabel != NULL);

	ObsCast(IControlEventsObserver, m_buySoftButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_buyHardButton)->AddObserver(this);
	ObsCast(IControlEventsObserver, m_activateButton)->AddObserver(this);

	return true;
}

bool DecalsPanelController::ReleaseResources()
{
	if (m_view != NULL)
		delete m_view;

	return true;
}

void DecalsPanelController::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_view->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void DecalsPanelController::Update(float time, float seconds)
{
	m_view->Update(time, seconds);
}

void DecalsPanelController::SelectDecal(const std::string& decalId)
{
	if (decalId == m_selectedDecalId)
		return;

	m_selectedDecalId = decalId;

	m_guiCar->LoadDecal(decalId);
}

void DecalsPanelController::BuyDecal(const std::string& decalId, bool buyForHard)
{
	assert(m_activeCar != NULL);
	assert(m_activeCar->HasDecal(decalId) == false);

	if (m_activeCar->HasDecal(decalId))
		return;

	CarData carData = GlobalSettings::GetCarById(m_activeCar->GetId());
	DecalData decalData = carData.GetDecalData(decalId);

	if (!buyForHard)
	{
		assert(decalData.SoftPrice > 0);

		if (Player::Instance->GetSoftMoney() < decalData.SoftPrice)
		{
			// not enouch soft money - message
			assert("not enouch soft money - message" && false);
		}

		Player::Instance->SetSoftMoney(Player::Instance->GetSoftMoney() - decalData.SoftPrice);
	}
	else
	{
		assert(decalData.HardPrice > 0);

		if (Player::Instance->GetHardMoney() < decalData.HardPrice)
		{
			// not enouch hard money - message
			assert("not enouch hard money - message" && false);
		}

		Player::Instance->SetHardMoney(Player::Instance->GetHardMoney() - decalData.HardPrice);
	}

	m_activeCar->AddDecal(decalData);

	ActivateDecal(decalId);
}

void DecalsPanelController::ActivateDecal(const std::string& decalId)
{
	assert(m_activeCar != NULL);
	assert(m_activeCar->HasDecal(decalId));

	if (!m_activeCar->HasDecal(decalId))
		return;

	m_activeCar->SetDecal(decalId);

	RefreshView();
}

void DecalsPanelController::HideAllActionPanels()
{
	m_buyPanel->SetVisible(false);
	m_activatePanel->SetVisible(false);
}

void DecalsPanelController::CreateDecalsButtons()
{
	assert(m_activeCar != NULL);

	m_decalButtonsGrid->RemoveAllChildren();

	CarData carData = GlobalSettings::GetCarById(m_activeCar->GetId());
	for (uint32_t i = 0; i < carData.Decals.size(); i++)
	{
		AnimButton* decalButton = CreateDecalButton(carData.Decals[i].Id);
		m_decalButtonsGrid->AddChild(decalButton);

		ObsCast(IControlEventsObserver, decalButton)->AddObserver(this);
	}
}

AnimButton* DecalsPanelController::CreateDecalButton(const std::string& decalId)
{
	TexPart* sprite = InterfaceProvider::m_atlases["atlas"]->GetTexPart("photo");

	AnimButton* button = new AnimButton(decalId, 0, 0, *sprite, *sprite);
	button->SetUserData("decal_id", decalId);

	return button;
}

void DecalsPanelController::RefreshView()
{
	assert(m_activeCar != NULL);

	CarData carData = GlobalSettings::GetCarById(m_activeCar->GetId());
	DecalData decalData = carData.GetDecalData(m_selectedDecalId);

	HideAllActionPanels();

	if (!m_activeCar->HasDecal(m_selectedDecalId))
	{
		m_buyPanel->SetVisible(true);

		m_softPriceLabel->SetText(StringUtils::ToString(decalData.SoftPrice));
		m_hardPriceLabel->SetText(StringUtils::ToString(decalData.HardPrice));

		if (decalData.SoftPrice > 0 && decalData.HardPrice > 0)
		{
			m_buySoftButton->SetAlign("bottom-left");
			m_buySoftButton->SetVisible(true);
			m_buyHardButton->SetAlign("bottom-right");
			m_buyHardButton->SetVisible(true);
		}
		else if (decalData.SoftPrice > 0)
		{
			m_buySoftButton->SetAlign("bottom");
			m_buySoftButton->SetVisible(true);
			m_buyHardButton->SetVisible(false);
		}
		else if (decalData.HardPrice > 0)
		{
			m_buyHardButton->SetAlign("bottom");
			m_buyHardButton->SetVisible(true);
			m_buySoftButton->SetVisible(false);
		}
	}
	else if (m_activeCar->HasDecal(m_selectedDecalId) && m_activeCar->GetActiveDecalId() != m_selectedDecalId)
		m_activatePanel->SetVisible(true);
}

void DecalsPanelController::HandlePress(int pointId, const sm::Vec2 &point)
{
	m_view->HandlePress(pointId, point);
}

void DecalsPanelController::HandleRelease(int pointId, const sm::Vec2 &point)
{
	m_view->HandleRelease(pointId, point);
}

void DecalsPanelController::HandleMove(int pointId, const sm::Vec2 &point)
{
	m_view->HandleMove(pointId, point);
}

void DecalsPanelController::Enter()
{
	m_activeCar = Player::Instance->GetActiveCar();
	if (m_activeCar == NULL)
		return;

	SelectDecal(m_activeCar->GetActiveDecalId());
	CreateDecalsButtons();
	RefreshView();
}

void DecalsPanelController::Leave()
{
	GuiCarUtils::LoadPlayerCar(m_guiCar);
}

void DecalsPanelController::SetActive(bool active)
{
	m_view->SetVisible(active);
}

void DecalsPanelController::Clicked(Control *control, uint32_t x, uint32_t y)
{
	if (control == m_buySoftButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		BuyDecal(m_selectedDecalId, false);
	}
	else if (control == m_buyHardButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		BuyDecal(m_selectedDecalId, true);
	}
	else if (control == m_activateButton)
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
		ActivateDecal(m_selectedDecalId);
	}
	else // probably decal button
	{
		SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);

		std::string decalId = control->GetUserData("decal_id");
		if (decalId.size() > 0)
		{
			SelectDecal(decalId);
			RefreshView();
		}
	}
}

void DecalsPanelController::ChangedDecal(Car* car, const std::string& decalId)
{
	RefreshView();
}
